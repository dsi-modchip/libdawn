@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>
#include <dawn/hw/addrspace.h>
#include <dawn/hw/iobase.h>

	.arch armv4t
	.cpu  arm7tdmi
	.arm

#define NUM_IRQ 47

.extern __isr_table
.extern __isr_sched


	@.weak __isr_scheduler_default
DAWN_BEGIN_FUNC_FASTMEM __isr_scheduler_default
	bx lr
DAWN_END_FUNC __isr_scheduler_default


	@ BIOS pushes r0-r3,r12,lr, then gets the ISR address from WRAM, and
	@ branches to it. VTOR base isn't configurable on ARM7
	.weak isr_handler
DAWN_BEGIN_FUNC_FASTMEM isr_handler
	@ cpu is now running in irq mode instead of sys mode
	@ lr and sp are different in irq mode than in sys mode, r0-r12 need to be saved
	@ pc to return to has been saved in lr_irq, cpsr of sys mode is now in spsr
	@ the cpu copies spsr back into cpsr automatically when returning

	@ register usage:
	@  r0: tmp/interrupt number
	@  r1: pending interrupt flag
	@  r2: tmp/interrupt handler function
	@  r3: tmp
	@ r12: base address (IO_IRQ or isr table)

	mov r12, #IO_BASE
	add r12, #(IO_IRQ_BASE-IO_BASE+0x10)

	ldr  r1, [r12, #-8]  @ REG_IME
	cmp  r1, #0
	bxeq lr              @ not enabled -> spurious

	ldmia r12!, {r0,r1}  @ REG_IE, REG_IF
	mov   r3, #1         @ prepare loop counter used in checkloop
	ands  r1, r0         @ if &= ie
	beq  .Lisr_if2       @ no enabled & flagged -> try IE2/IF2

	@ find first pending irq (there may be multiple active!)
	@ priority is from high bit to low bit, not optimal but eh
	mov   r0, #0x1f
.Lcheckloop_lo:
	ands  r2, r1, r3, lsl r0
	subeq r0, #1
	beq  .Lcheckloop_lo  @ no need to check for r0==0, r1 checked for nonzero already

	@ ack interrupt (both to HW and to BIOS)
	str r2, [r12, #4]    @ REG_IF -> ack interrupt
	b  .Lisr_handle

.Lisr_if2:
	ldmia r12!, {r0,r1}  @ REG_IE2, REG_IF2
	ands  r1, r0         @ if &= ie
	bxeq  lr             @ no enabled & flagged -> spurious

	mov   r0, #0xe       @ IE2/IF2 have no flags in upper 16 bits
.Lcheckloop_hi:
	ands  r2, r1, r3, lsl r0
	subeq r0, #1
	beq  .Lcheckloop_hi  @ again, guaranteed to terminate

	str r2, [r12, #4]    @ REG_IF2 -> ack interrupt
	add r0, #0x20

.Lisr_handle:
	@ look up the resulting number in the ISR table
	ldr r12, =__isr_table
	ldr  r2, [r12, r0, lsl #2]
	@cmp  r2, #0
	@beq .Lisr_end         @ only handle if pointer is nonzero  @ always inited to default

	@ enable ISR reentrantability(? is that a word?), switch to sys mode for larger stack
	mrs   r3, spsr        @ back up spsr
	push {r3}
	msr  cpsr_c, #0x5f    @ sys mode, FIQ disabled but IRQ enabled
	str   lr, [sp, #-4]!  @ push {lr} but not using ldm: ldm instructions may
                          @ be interrupted in the middle of transfer, and are
                          @ restarted on IRQ return! by this time, lr will have
                          @ the wrong value and the nested ISR will crash upon
                          @ returning. IRQ enable has an effect latency of one
                          @ cycle, thus, this str instruction effectively
                          @ cannot be interrupted

	@ jump to the handler
	mov lr, pc
	bx  r0                @ AAPCS: allowed to overwrite r0-r3,r12,cpsr

	@ undo previous stuff for a graceful return to irq mode
	pop  {lr}
	msr  cpsr_c, #0xd2    @ irq mode, IRQ and FIQ disabled
	pop  {r3}
	msr spsr_cxsf, r3

	@ TODO: jump to scheduler
	bx lr  @ return to BIOS (which will return to regular execution)

	.pool
DAWN_END_FUNC isr_handler

