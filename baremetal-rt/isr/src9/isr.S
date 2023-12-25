@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>
#include <dawn/hw/addrspace.h>
#include <dawn/hw/iobase.h>

	.arch armv5te
	.cpu  arm946e-s
	.arm

#define NUM_IRQ 32

.extern __isr_table
.extern __isr_sched


	@.weak __isr_scheduler_default
DAWN_BEGIN_FUNC_FASTMEM __isr_scheduler_default
	bx lr
DAWN_END_FUNC __isr_scheduler_default


	.weak VTOR_IRQ
DAWN_BEGIN_FUNC_FASTMEM VTOR_IRQ
	push {r0-r3,r12,lr}
	@ BIOS also pushes lr, then gets the ISR address from DTCM[-4], and
	@ branches to it, let's skip that

	@ if VTOR is at BIOS, lr will be 0xffff0140 at ISR entry
	.weak isr_handler
DAWN_BEGIN_FUNC_NOSEC isr_handler
	@ cpu is now running in irq mode instead of sys mode
	@ lr and sp are different in irq mode than in sys mode, r0-r12 need to be saved
	@ pc to return to has been saved in lr_irq, cpsr of sys mode is now in spsr
	@ the cpu copies spsr back into cpsr automatically when returning
	@ returning from an interrupt is done by running the following instruction:
	@     subs pc, lr, #4

	@ register usage:
	@  r0: tmp/interrupt number
	@  r1: pending interrupt flag
	@  r2: tmp/interrupt handler function
	@  r3: tmp
	@ r12: base address (IO_IRQ or DTCM or isr table)

	mov r12, #IO_BASE
	add r12, #(IO_IRQ_BASE-IO_BASE+0x10)

	ldr  r1, [r12, #-8]  @ REG_IME
	cmp  r1, #0
	beq .Lisr_end        @ not enabled -> spurious

	ldrd r0, [r12]       @ r0=REG_IE, r1=REG_IF
	ands r1, r0          @ if &= ie
	beq .Lisr_end        @ no enabled & flagged -> spurious

	@ find first pending irq (there may be multiple active!)
	@ priority is from high bit to low bit, not optimal but eh
	mov  r3, #(1<<(NUM_IRQ-1))
.Lcheckloop:
	clz  r0, r1
	bics r1, r3, lsr r0  @ clear from pending list
	bne .Lcheckloop

	@ ack interrupt (both to HW and to BIOS)
	mov  r1, r3, lsr r0
	str  r1, [r12, #4]          @ REG_IF -> ack interrupt
	mrc p15, 0, r12, c9, c1, 0  @ read DTCM info
	lsr r12, #12                @ shave off lower 12 bits (discard size settings)
	lsl r12, #12
	add r12, #0x4000            @ go to end of DTCM
	ldr  r2, [r12, #-8]         @ SWI_IntrWait IRQ CHECKFLAG
	orr  r2, r1
	str  r2, [r12, #-8]

	@ look up the resulting number in the ISR table
	ldr r12, =__isr_table
	rsbs r0, #0x1f
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
	blx   r2              @ AAPCS: overwrites r0-r3,r12,cpsr; blx trashes lr

	@ undo previous stuff for a graceful return to irq mode
	pop  {lr}
	msr  cpsr_c, #0xd2    @ irq mode, IRQ and FIQ disabled
	pop  {r3}
	msr spsr_cxsf, r3

.Lisr_end:
	@ TODO: call scheduler

	@ this comparison holds for addresses in the range 0xffff:0140..:015f
	@ this range also contains 6 addresses that are part of the SWI handler.
	@ however, interrupts are disabled in the CPSR on SWI entry, so this is
	@ fine as no IRQs can be handled in this code
	asr  r0, lr, #5
	cmp  r0, #0xffffff0a  @ 0xffff0140 >> 5 (arithmetic shift), constant fits in an immediate
	bxeq lr               @ return to BIOS code, as we were called by the BIOS handler

	pop {r0-r3,r12}       @ pop saved registers
	subs pc, lr, #4       @ return from interrupt (CPU recognises this to also restore spsr to cpsr)

	.pool
DAWN_END_FUNC isr_handler
DAWN_END_FUNC VTOR_IRQ

