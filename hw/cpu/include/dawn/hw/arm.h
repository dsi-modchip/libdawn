
#ifndef DAWN_HW_CPU_ARM_H_
#define DAWN_HW_CPU_ARM_H_

#ifndef __arm__
#error "This code must be used on an ARM CPU!"
#endif

#include <stdint.h>

#include <dawn/util/macro.h>


enum cpsr_cpu_mode {
	cpsr_mode_usr = 0x10,
	cpsr_mode_fiq = 0x11,
	cpsr_mode_irq = 0x12,
	cpsr_mode_svc = 0x13,
	/* mon = 0x16 // secure monitor (TZ) */
	cpsr_mode_abt = 0x17,
	/* hyp = 0x1a // hypervisor */
	cpsr_mode_und = 0x1b,
	cpsr_mode_sys = 0x1f,
};


uint32_t cpsr_get(void);
uint32_t cpsr_set(uint32_t v);

uint32_t cpsr_irq_enable(void);
uint32_t cpsr_irq_disable(void);
uint32_t cpsr_irq_set(uint32_t mask);
uint32_t cpsr_irq_set_ptr(const uint32_t* mask);
uint32_t cpsr_get_irq_enabled(void);

uint32_t cpsr_fiq_enable(void);
uint32_t cpsr_fiq_disable(void);
uint32_t cpsr_fiq_set(uint32_t mask);
uint32_t cpsr_fiq_set_ptr(const uint32_t* mask);
uint32_t cpsr_get_fiq_enabled(void);

uint32_t cpsr_irqfiq_enable(void);
uint32_t cpsr_irqfiq_disable(void);
uint32_t cpsr_irqfiq_set(uint32_t mask);
uint32_t cpsr_irqfiq_set_ptr(const uint32_t* mask);

uint32_t cpsr_get_mode(void);

#ifdef ARM7
void cpu_wfi_haltcnt(void);
#endif


#define CRITICAL_SECTION(...) \
	do { /* also works in case a return statement is present in __VA_ARGS__ */ \
		__attribute__((__cleanup__(cpsr_irq_set_ptr))) \
		uint32_t __cpsrbak = cpsr_irq_disable(); \
		{ __VA_ARGS__ ;}; \
		/*cpsr_irq_set(__cpsrbak);*/ /* cleanup attr does this for us */ \
	} while (0) \


#endif

