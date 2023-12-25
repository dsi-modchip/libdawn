@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>
#include <dawn/hw/scfg/regs.h>

#include <dawn/hw/dsp/regs.h>

DAWN_BEGIN_FUNC dsp_poweron, .itcm.text.dsp_poweron
	ldr  r0, =IO_SCFG_BASE

	ldrh r1, [r0, #6]  @ SCFG_RST
	bic  r1, #REG_SCFG_RST_DSP_Msk
	strh r1, [r0, #6]

	ldrh r2, [r0, #4]  @ SCFG_CLK
	orr  r2, #REG_SCFG_CLK_DSP_Msk
	strh r2, [r0, #4]

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	orr  r1, #REG_SCFG_RST_DSP_Msk
	strh r1, [r0, #6]

	bx lr

	.pool
DAWN_END_FUNC dsp_poweron


DAWN_BEGIN_FUNC dsp_reset
	ldr r3, =IO_DSP_BASE

	ldrh r2, [r3, #8]  @ DSP_PCFG
	orr  r2, #REG_DSP_PCFG_RST_Msk
	strh r2, [r3, #8]

	cmp  r0, #0
	bxeq lr  @ return now, leaving DSP in reset, if arg0 is false

	@ clear IRQ enable flags
	bic  r0, #(REG_DSP_PCFG_IE_REP0_Msk|REG_DSP_PCFG_IE_REP1_Msk|REG_DSP_PCFG_IE_REP2_Msk)
	strh r0, [r3, #8]

	@ set PMASK to 0, PCLEAR to 0xffff
	mov  r0, #0
	strh r0, [r3, #0x10]  @ DPS_PMASK
	mvn  r0, #0
	strh r0, [r3, #0x18]  @ DSP_PCLEAR

	@ dummy read REPx to reinit status
	ldrh r0, [r3, #0x24]  @ DSP_REP0
	ldrh r0, [r3, #0x2c]  @ DSP_REP1
	ldrh r0, [r3, #0x34]  @ DSP_REP2

	@ wait until DSP inited
1:	ldrh r0, [r3, #0xc]  @ DSP_PSTS
	tst  r0, #REG_DSP_PSTS_PRST_Msk
	bne  1b

	lsr  r0, r1, #16
	strh r0, [r3, #0x10]  @ DSP_PMASK

	@ bring DSP out of reset, this makes the DSP execute its reset vactor
	@ also set IE bits in PCFG while we're at it
	and  r1, #0x0fe0  @ DSP_PCFG.IE_*
	orr  r2, r1
	bic  r2, #REG_DSP_PCFG_RST_Msk
	strh r2, [r3, #8]  @ DSP_PCFG

	bx lr
DAWN_END_FUNC dsp_reset


DAWN_BEGIN_FUNC dsp_poweroff
	ldr r0, =IO_SCFG_BASE
	add r2, r0, #(IO_DSP_BASE-IO_SCFG_BASE)

	@ hold DSP core in reset
	ldrh r1, [r0, #8]  @ DSP_PCFG
	orr  r1, #REG_DSP_PCFG_RST_Msk
	strh r1, [r0, #8]

	@ hold DSP block in reset
	ldrh r1, [r2, #6]  @ SCFG_RST
	bic  r1, #REG_SCFG_RST_DSP_Msk
	strh r1, [r2, #6]

	@ stop providing a clock signal to the DSP block
	ldrh r1, [r2, #4]  @ SCFG_CLK
	bic  r1, #REG_SCFG_CLK_DSP_Msk
	strh r1, [r2, #4]
DAWN_END_FUNC dsp_poweroff

