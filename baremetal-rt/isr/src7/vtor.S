@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>
#include <dawn/hw/addrspace.h>
#include <dawn/hw/iobase.h>

	.arch armv4t
	.cpu  arm7tdmi
	.arm

.extern __libdawn_handle_error


	.weak VTOR_BIOS_DEBUG
DAWN_BEGIN_FUNC_FASTMEM VTOR_BIOS_DEBUG
	@ luckily, unlike the ARM9, the ARM7 BIOS does use a sensible stack (IWRAM)
	@ there's also no mpu control register to backup and stuff
	mov r12, sp            @ back up old stack pointer because we'll need it
@	sub sp, #(17*4+1)      @ allocate space. also realign because AUGH
	@ twl7 IF2 check flags are at +ffc0 so we can't just allocate linearly from
	@ the stack as we'd be overwriting it. instead, start allocating from there
	ldr sp, =__sp_und  @ 0x0380ff60

	str lr, [sp, #-4]      @ back up lr (differs between NTR and TWL BIOS)
	@ back up crash dump info
	ldr lr, [r12, #12]     @ usermode pc+4
	str lr, [sp, #(15*4)]
	ldr lr, [r12, # 4]     @ usermode cpsr
	str lr, [sp, #(16*4)]
	ldr r12, [r12, #8]     @ get original r12
	stm sp, {r0-r14}^      @ '^' is a magic token that makes it push the user mode regs instead

	@ call handler
	mov r0, sp
	sub sp, #4     @ 'push' cf "str lr, [sp, #-4]" above
	bl  __libdawn_handle_error@(ptr)

	pop {lr}
	@ get back usermode regs now
	ldm  sp, {r0-r14}^      @ this writes to lr_usr, not lr_abt/und
	@ return to BIOS. it will put back spsr and pc_usr on its own
	ldr  sp, =(0x0380ffdc+1-8*2)
	bx   lr

	.pool
DAWN_END_FUNC VTOR_BIOS_DEBUG

