@ vim: set ft=armv4:

	.arch armv4t
	.arm

#include <dawn/hw/asminc.h>

DAWN_BEGIN_FUNC_FASTMEM cpsr_get
	mrs r0, cpsr
	bx  lr
DAWN_END_FUNC cpsr_get

DAWN_BEGIN_FUNC_FASTMEM cpsr_set
	mrs r1, cpsr
	msr cpsr, r0
	mov r0, r1
	bx  lr
DAWN_END_FUNC cpsr_set

DAWN_BEGIN_FUNC_FASTMEM cpsr_irq_enable
	mrs r0, cpsr
	bic r1, r0, #0x80
	msr cpsr, r1
	and r0, #0x80
	bx  lr
DAWN_END_FUNC cpsr_irq_enable

DAWN_BEGIN_FUNC_FASTMEM cpsr_irq_disable
	mrs r0, cpsr
	orr r1, r0, #0x80
	msr cpsr, r1
	and r0, #0x80
	bx  lr
DAWN_END_FUNC cpsr_irq_disable

DAWN_BEGIN_FUNC_FASTMEM cpsr_irq_set_ptr
	ldr r0, [r0]
DAWN_BEGIN_FUNC_NOSEC cpsr_irq_set
	mrs r1, cpsr
	bic r2, r1, #0x80
	orr r2, r0
	msr cpsr, r2
	and r0, r1, #0x80
	bx  lr
DAWN_END_FUNC cpsr_irq_set
DAWN_END_FUNC cpsr_irq_set_ptr

DAWN_BEGIN_FUNC_FASTMEM cpsr_get_irq_enabled
	mrs r0, cpsr
	and r0, #0x80
	bx  lr
DAWN_END_FUNC cpsr_get_irq_enabled




DAWN_BEGIN_FUNC_FASTMEM cpsr_fiq_enable
	mrs r0, cpsr
	bic r1, r0, #0x40
	msr cpsr, r1
	and r0, #0x40
	bx  lr
DAWN_END_FUNC cpsr_fiq_enable

DAWN_BEGIN_FUNC_FASTMEM cpsr_fiq_disable
	mrs r0, cpsr
	orr r1, r0, #0x40
	msr cpsr, r1
	and r0, #0x40
	bx  lr
DAWN_END_FUNC cpsr_fiq_disable

DAWN_BEGIN_FUNC_FASTMEM cpsr_fiq_set_ptr
	ldr r0, [r0]
DAWN_BEGIN_FUNC_NOSEC cpsr_fiq_set
	mrs r1, cpsr
	bic r2, r1, #0x40
	orr r2, r0
	msr cpsr, r2
	and r0, r1, #0x40
	bx  lr
DAWN_END_FUNC cpsr_fiq_set
DAWN_END_FUNC cpsr_fiq_set_ptr

DAWN_BEGIN_FUNC_FASTMEM cpsr_get_fiq_enabled
	mrs r0, cpsr
	and r0, #0x40
	bx  lr
DAWN_END_FUNC cpsr_get_fiq_enabled



DAWN_BEGIN_FUNC_FASTMEM cpsr_irqfiq_enable
	mrs r0, cpsr
	bic r1, r0, #0xc0
	msr cpsr, r1
	and r0, #0xc0
	bx  lr
DAWN_END_FUNC cpsr_irqfiq_enable

DAWN_BEGIN_FUNC_FASTMEM cpsr_irqfiq_disable
	mrs r0, cpsr
	orr r1, r0, #0xc0
	msr cpsr, r1
	and r0, #0xc0
	bx  lr
DAWN_END_FUNC cpsr_irqfiq_disable

DAWN_BEGIN_FUNC_FASTMEM cpsr_irqfiq_set_ptr
	ldr r0, [r0]
DAWN_BEGIN_FUNC_NOSEC cpsr_irqfiq_set
	mrs r1, cpsr
	bic r2, r1, #0xc0
	orr r2, r0
	msr cpsr, r2
	and r0, r1, #0xc0
	bx  lr
DAWN_END_FUNC cpsr_irqfiq_set
DAWN_END_FUNC cpsr_irqfiq_set_ptr



DAWN_BEGIN_FUNC_FASTMEM cpsr_get_mode
	mrs r0, cpsr
	and r0, #0x1f
	bx  lr
DAWN_END_FUNC cpsr_get_mode

