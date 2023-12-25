@ vim: set ft=armv4:

#include <dawn/hw/asminc.h>
#include <dawn/hw/addrspace.h>
#include <dawn/hw/dma/regs.h>
#include <dawn/hw/ndma/regs.h>
#include <dawn/hw/pxi/regs.h>

	.arch armv4t
	.cpu  arm7tdmi
	.arm

	.extern _start
	.extern __crt0_setup_data_and_bss
	.extern __crt0_hardware_init
	.extern dawn_hw_model_get

	.extern __sp_irq
	.extern __sp_svc
	.extern __sp_usr


.macro crt0_sync_send no
	mov r1, #((\no\())<<REG_IPCSYNC_TOCPU_Lsb)
	str r1, [r4]  @ REG_IPCSYNC
.endm
.macro crt0_sync_wait no
	@@ wait for magic sync value
999:
	ldr r1, [r4]  @ REG_IPCSYNC
	and r1, #REG_IPCSYNC_FROMCPU_Msk
	cmp r1, #(\no\())
	bne 999b
.endm
.macro crt0_sync no
	crt0_sync_send (\no\())
	crt0_sync_wait ((\no\())+1)
.endm


DAWN_BEGIN_FUNC ResetHandler, .text.startup.ResetHandler
	@ disable interrupts through REG_IME
	mov r12, #IO_BASE
	str r12, [r12, #0x208]
	@ disable ongoing DMA transfers
	mov r0, #0
	ldr r1, =REG_DMA_WCNT_ADDR(0)
	str r0, [r1, #(12*0)]
	str r0, [r1, #(12*1)]
	str r0, [r1, #(12*2)]
	str r0, [r1, #(12*3)]
	ldr r1, =REG_NDMAxCNT_ADDR(0)
	str r0, [r1, #(0x1c*0)]
	str r0, [r1, #(0x1c*1)]
	str r0, [r1, #(0x1c*2)]
	str r0, [r1, #(0x1c*3)]

	@ initialize CPU modes and stacks:
	@@ IRQ mode: __sp_irq, disable irq & fiq
	mov r0, #0x12
	msr cpsr, r0
	ldr sp, =__sp_irq
	@@ SVC mode: __sp_svc, disable irq & fiq
	mov r0, #0x13
	msr cpsr, r0
	ldr sp, =__sp_svc
	@@ - don't do abort and undef insn modes. we can't control it because of
	@@   the BIOS anyway. the libdawn handler uses the stack at 0x0380ff60.
	@@ system mode: __sp_usr, disable irq & fiq
	mov r0, #0x1f
	msr cpsr, r0
	ldr sp, =__sp_usr

	@ sync with ARM9:
	ldr r4, =REG_IPCSYNC_ADDR
	ldr r5, =REG_IPCFIFORECV_ADDR
	@@ 0. enable FIFO interface
	mov r0, #REG_IPCFIFOCNT_EN_Msk
	str r0, [r4, #4]  @ REG_IPCFIFOCNT
	@@ 1. clear FIFO
1:	ldr r0, [r4, #4]  @ REG_IPCFIFOCNT
	tst r0, #REG_IPCFIFOCNT_RECV_EMPTY_Msk
	ldreq r0, [r5]  @ REG_IPCFIFORECV
	beq 1b          @ eq = bit not set = not empty
	@@ 2. do sync
	crt0_sync 8

	@ detect hardware model & send it to ARM9
	bl  dawn_hw_model_get
	str r0, [r4, #8]  @ REG_IPCFIFOSEND

	@ wait for WRAM mapping
	crt0_sync_wait 10

	@ now, set up data and bss
	bl __crt0_setup_data_and_bss  @ r0 = hardware model, still

	@ call hardware init routine. this will set up the exception and interrupt
	@ vectors and so on.
	crt0_sync 11
	bl __crt0_hardware_init

	@ call _start, which does the language runtime stuff with global
	@ constructors and destructors if needed. also calls exit() at the end so
	@ this should never return
	crt0_sync 13
	crt0_sync_send 0
	b _start

	.pool
DAWN_END_FUNC ResetHandler

