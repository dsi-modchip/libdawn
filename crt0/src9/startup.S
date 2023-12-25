@ vim: set ft=armv5:

#include <dawn/options.h>
#include <dawn/hw/asminc.h>
#include <dawn/hw/addrspace.h>
#include <dawn/hw/dma/regs.h>
#include <dawn/hw/memory/regs.h>
#include <dawn/hw/ndma/regs.h>
#include <dawn/hw/pxi/regs.h>


	.arch armv5te
	.cpu  arm946e-s
	.arm

	.extern _start
	.extern __crt0_setup_data_and_bss
	.extern __crt0_hardware_init

	.extern __dtcm_base
	.extern __sp_irq
	.extern __sp_svc
	.extern __sp_usr

	.extern __dawn_hw_model_type
	.extern __WRAMCNT_DEFAULT


	.section .rodata.__WRAMCNT_DEFAULT
	.global __WRAMCNT_DEFAULT
	.type __WRAMCNT_DEFAULT, %object
	.weak __WRAMCNT_DEFAULT
__WRAMCNT_DEFAULT:
	.byte 3  @ all to ARM7
	.size __WRAMCNT_DEFAULT, . - __WRAMCNT_DEFAULT


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
	crt0_sync_wait (\no\())
	crt0_sync_send ((\no\())+1)
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

	@ do the first bit of CP15 initialization:
	@ * disable the MPU (and, with it, disable caching)
	@ * set the ITCM size to 0x0200_0000
	@ * set the DTCM address to 0x0b00_0000

	@ MPU disable; DC enable; wrbuf enable; little endian; icache enable;
	@ high exn vectors; round-robin cache replacement; ARMv5 ldm/ldr;
	@ DTCM enable; no DTCM loadmode; ITCM enable; no ITCM loadmode
	ldr r0, =((0<<0)|(1<<2)|(1<<3)|(0<<7)|(1<<12)|(1<<13)|(1<<14)|(0<<15)|(1<<16)|(0<<17)|(1<<18)|(0<<19))
	mcr p15, 0, r0, c1, c0, 0
	@ ITCM size
	mov r0, #(16<<1)  @ ITCM size: 0x0200_0000
	mcr p15, 0, r0, c9, c1, 0
	@ DTCM base address
	ldr r8, =__dtcm_base
	orr r8, #(5<<1)  @ DTCM size: 16k = 512<<5
	mcr p15, 0, r8, c9, c1, 0
	@ now calculate the abt/und stack top
	add r8, #(LIBDAWN_DTCM_STACK_SIZE - 0x80)

	@ initialize CPU modes and stacks:
	@@ IRQ mode: __sp_irq, disable irq & fiq
	mov r0, #0x12
	msr cpsr, r0
	ldr sp, =__sp_irq
	@@ SVC mode: __sp_svc, disable irq & fiq
	mov r0, #0x13
	msr cpsr, r0
	ldr sp, =__sp_svc
	@@ abort mode: __sp_abt, disable irq & fiq
	mov r0, #0x17
	msr cpsr, r0
	mov sp, r8
	@@ undef. insn. mode: also __sp_abt, disable irq & fiq
	mov r0, #0x1b
	msr cpsr, r0
	mov sp, r8
	@@ system mode: __sp_usr, disable irq & fiq
	mov r0, #0x1f
	msr cpsr, r0
	ldr sp, =__sp_usr

	@ sync with ARM7:
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

	@ get detected hardware model from ARM7
	ldr r6, =__twl_hw_model_type
1:	ldr r0, [r4, #4]  @ REG_IPCFIFOCNT
	tst r0, #REG_IPCFIFOCNT_RECV_EMPTY_Msk
	beq 1b  @ wait until nonempty
	ldr r0, [r5]  @ REG_IPCFIFORECV
	str r0, [r6]

	@ put WRAM mapping in order: WRAMCNT
	ldr  r1, =__WRAMCNT_DEFAULT
	ldr  r6, =REG_WRAMCNT_ADDR
	strb r1, [r6]

	crt0_sync_send 10

	@ now, set up data and bss
	bl __crt0_setup_data_and_bss  @ r0 = hardware model, still

	@ call hardware init routine. this will set up the exception and interrupt
	@ vectors, init the MPU, and so on.
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

