@ vim: set ft=armv5:

#include <dawn/options.h>
#include <dawn/hw/asminc.h>
#include <dawn/hw/addrspace.h>
#include <dawn/hw/iobase.h>

	.arch armv5te
	.cpu  arm946e-s
	.arm

.extern __libdawn_handle_error
.extern VTOR_IRQ


	.section .vectors, "ax", %progbits
	.global VECTORS
	.type VECTORS, %object
	.weak VECTORS
VECTORS:
	@ reset handler. on SoC reset, the VTORBASE will be moved back to BIOS so
	@ its reset handler will run. we can thus put whatever here, it doesn't
	@ matter much
H_RST:  	.4byte 0x6276646c  @ "ldvb"; LibDawnVtorBase (cf. sysinit/system.c)
H_UND:  	b VTOR_UND  @ woof
H_SWI:  	b VTOR_SWI
H_PABRT:	b VTOR_PABRT
H_DABRT:	b VTOR_DABRT
H_RES:  	b H_RES     @ reserved
H_IRQ:  	b VTOR_IRQ
H_FIQ:  	b H_FIQ     @ no FIQs ever occur
	.size VECTORS, . - VECTORS


	.weak VTOR_SWI
DAWN_BEGIN_FUNC_FASTMEM VTOR_SWI
	b 0xffff0008       @ BIOS SWI handler
DAWN_END_FUNC VTOR_SWI


	.weak VTOR_UND
DAWN_BEGIN_FUNC_FASTMEM VTOR_UND
	msr cpsr_f, #(0<<29)  @ save exn type in cpsr flags
	b VTOR_exn_common

	.weak VTOR_PABRT
DAWN_BEGIN_FUNC_NOSEC   VTOR_PABRT
	msr cpsr_f, #(1<<29)
	b VTOR_exn_common

	.weak VTOR_DABRT
DAWN_BEGIN_FUNC_NOSEC   VTOR_DABRT
	msr cpsr_f, #(2<<29)
	@b VTOR_exn_common

VTOR_exn_common:
	@ need to keep r0-r12 alive for exception handling code! -> use sp as tmp

	@ not needed, done by hw on exception entry and fiq doesn't exist on hw
	@msr cpsr_c, #0xdb  @ und mode, disable IRQ, FIQ

	@ get DTCM end address to get a proper stack
	mrc p15, 0, sp, c9, c1, 0
	lsr sp, #12
	lsl sp, #12
	add sp, #LIBDAWN_DTCM_STACK_SIZE
	sub sp, #(0x18*4)      @ allocate size for register backup

	@ back up crash dump info (1)
	str lr, [sp, #(15*4)]  @ usermode pc+4
	mrs lr, spsr
	str lr, [sp, #(16*4)]  @ usermode cpsr

	@ disable mpu
	mrc p15, 0, lr, c1, c0, 0
	str lr, [sp, #(17*4)]  @ mpu control register
	bic lr, #1
	mcr p15, 0, lr, c1, c0, 0

	@ back up crash dump info
	stm sp, {r0-r14}^   @ '^' is a magic token that makes it push the user mode regs instead

	@ call handler
	mov r0, sp
	mrs r1, cpsr
	lsr r1, #29    @ exception type is still saved here as we used no s-suffix insns
	bl  __libdawn_handle_error@(magic, ptr, mode)

@	@ we returned? time to panic and run around in a circle
@	msr cpsr_c, #0xdb
@1:	bkpt #0xdead
@	b 1b
	@ actually no, do exit gracefully for once

	ldr r0, [sp, #(16*4)]  @ usermode spsr
	msr spsr, r0
	ldr lr, [sp, #(15*4)]  @ usermode pc+4

	@ put MPU in old state
	ldr r0, [sp, #(17*4)]
	mcr p15, 0, r0, c1, c0, 0

	@ get back usermode regs now
	ldm sp, {r0-r14}^      @ this writes to lr_usr, not lr_abt/und

	@ finally, return
	subs pc, lr, #4

	.pool
DAWN_END_FUNC VTOR_DABRT
DAWN_END_FUNC VTOR_PABRT
DAWN_END_FUNC VTOR_UND


	.weak VTOR_BIOS_DEBUG
DAWN_BEGIN_FUNC_FASTMEM VTOR_BIOS_DEBUG
	@ whoo boy. this one's a bit of a doozy. the ARM9 BIOS uses some hardcoded
	@ main RAM memory to save the current state instead of the DTCM, which
	@ sucks. so we'll have to do a bit of register shuffling to keep things in
	@ order without using main RAM too much

	@ first of all, back up the main RAM stack pointer, and use a new one
	mov r12, sp      @ value differs between NTR and TWL BIOS
	mrc p15, 0, sp, c9, c1, 0
	lsr sp, #12
	lsl sp, #12
	add sp, #(LIBDAWN_DTCM_STACK_SIZE - 0x80)
	sub sp, #(0x18*4)      @ allocate size for register backup
	                       @ 0x60 bytes left...

	str lr, [sp, #-4]      @ back up lr (differs between NTR and TWL BIOS)
	@ back up crash dump info
	ldr lr, [r12, #12]     @ usermode pc+4
	str lr, [sp, #(15*4)]
	ldr lr, [r12, # 4]     @ usermode cpsr
	str lr, [sp, #(16*4)]
	ldr lr, [r12]          @ mpu control reg (already backed up & disabled by BIOS)
	str lr, [sp, #(17*4)]
	ldr r12, [r12, #8]     @ get original r12
	stm sp, {r0-r14}^      @ '^' is a magic token that makes it push the user mode regs instead

	@ call handler
	mov r0, sp
	mov r1, #3     @ exception type
	sub sp, #4     @ 'push' cf "str lr, [sp, #-4]" above
	bl  __libdawn_handle_error@(magic, ptr, mode)

	pop {lr}
	@ get back usermode regs now
	ldm  sp, {r0-r14}^      @ this writes to lr_usr, not lr_abt/und
	@ return to BIOS. it will put back spsr, pc_usr, and mpuctl on its own
	ldr  sp, =(0x02fffd9c+1-8*2)
	bx   lr

	.pool
DAWN_END_FUNC VTOR_BIOS_DEBUG

