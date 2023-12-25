@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>

#include <dawn/hw/scfg/regs.h>

	.arch armv5te
	.cpu  arm946e-s

	.arm

DAWN_BEGIN_FUNC scfg_set_twl_clk, .itcm.text.scfg_set_twl_clk
	ldr   r1, =IO_SCFG_BASE
	cmp   r0, #0
	ldrh  r2, [r1, #4]  @ SCFG_CLK
	biceq r2, #1
	orrne r2, #1
	strh  r2, [r1, #4]

	@ "Change ARM9 clock only from code within ITCM (and wait at least 8 cycles
	@  before accessing any non-ITCM memory)."
	@ -GBATEK
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	bx lr

	.pool
DAWN_END_FUNC scfg_set_twl_clk

