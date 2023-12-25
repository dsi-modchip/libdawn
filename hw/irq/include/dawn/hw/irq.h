
#ifndef DAWN_HW_IRQ_H_
#define DAWN_HW_IRQ_H_

#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/arm.h>
#ifdef ARM9
#include <dawn/hw/cpu/cp15.h>
#endif

#include <dawn/hw/irq/struct.h>


typedef void (*isr_fn_t)(void);

#ifdef ARM7
typedef uint64_t irq_flags_t;
#elif defined(ARM9)
typedef uint32_t irq_flags_t;
#endif


static inline isr_fn_t vtor_debug_get(void) {
	return (isr_fn_t)VTOR_HANDLE_DBG;
}
static inline isr_fn_t vtor_debug_set(isr_fn_t newisr) {
	isr_fn_t r = VTOR_HANDLE_DBG;
	VTOR_HANDLE_DBG = newisr;
	return r;
}

static inline isr_fn_t irq_main_isr_get(void) {
#ifdef ARM7
	return (isr_fn_t)VTOR_HANDLE_IRQ;
#elif defined(ARM9)
	uintptr_t addr = (cp15_dtcm_get_base() & 0xfffff000) + VTOR_HANDLE_IRQ_OFF;
	return *(isr_fn_t*)addr;
#endif
}
static inline isr_fn_t irq_main_isr_set(isr_fn_t newisr) {
	isr_fn_t r;
#ifdef ARM7
	r = VTOR_HANDLE_IRQ;
	VTOR_HANDLE_IRQ = newisr;
	return r;
#elif defined(ARM9)
	uintptr_t addr = (cp15_dtcm_get_base() & 0xfffff000) + VTOR_HANDLE_IRQ_OFF;
	r = *(isr_fn_t*)addr;
	*(isr_fn_t*)addr = newisr;
	return r;
#endif
}

static inline bool irq_main_enable_get(void) {
	return (REG_IRQ_HW.ime & 1) != 0;
}
static inline void irq_main_enable_set(bool v) {
	REG_IRQ_HW.ime = v ? 1 : 0;
}

static inline irq_flags_t irq_enable_get(void) {
#ifdef ARM7
	return REG_IRQ_HW.ie | ((uint64_t)REG_IRQ_HW.ie2 << 32);
#elif defined(ARM9)
	return REG_IRQ_HW.ie;
#endif
}
static inline irq_flags_t irq_enable_set(irq_flags_t flags) {
	irq_flags_t r;
#ifdef ARM7
	r = REG_IRQ_HW.ie | ((uint64_t)REG_IRQ_HW.ie2 << 32);
	REG_IRQ_HW.ie = flags;
	REG_IRQ_HW.ie2 = flags >> 32;
#elif defined(ARM9)
	r = REG_IRQ_HW.ie;
	REG_IRQ_HW.ie = flags;
#endif
	return r;
}
static inline irq_flags_t irq_enable_flags_en(irq_flags_t flags) {
	irq_flags_t r;
#ifdef ARM7
	r = REG_IRQ_HW.ie | ((uint64_t)REG_IRQ_HW.ie2 << 32);
	REG_IRQ_HW.ie = flags | r;
	REG_IRQ_HW.ie2 = (flags | r) >> 32;
#elif defined(ARM9)
	r = REG_IRQ_HW.ie;
	REG_IRQ_HW.ie = flags | r;
#endif
	return r;
}
static inline irq_flags_t irq_enable_flags_dis(irq_flags_t flags) {
	irq_flags_t r;
#ifdef ARM7
	r = REG_IRQ_HW.ie | ((uint64_t)REG_IRQ_HW.ie2 << 32);
	REG_IRQ_HW.ie = r & ~(uint64_t)flags;
	REG_IRQ_HW.ie2 = (r & ~(uint64_t)flags) >> 32;
#elif defined(ARM9)
	r = REG_IRQ_HW.ie;
	REG_IRQ_HW.ie = r & ~flags;
#endif
	return r;
}


static inline irq_flags_t irq_flags_get(void) {
#ifdef ARM7
	return REG_IRQ_HW.iflg | ((uint64_t)REG_IRQ_HW.if2 << 32);
#elif defined(ARM9)
	return REG_IRQ_HW.iflg;
#endif
}
static inline irq_flags_t irq_flags_set(irq_flags_t flags) {
	irq_flags_t r;
#ifdef ARM7
	r = REG_IRQ_HW.iflg | ((uint64_t)REG_IRQ_HW.if2 << 32);
	REG_IRQ_HW.iflg = flags;
	REG_IRQ_HW.if2 = flags >> 32;
#elif defined(ARM9)
	r = REG_IRQ_HW.iflg;
	REG_IRQ_HW.iflg = flags;
#endif
	return r;
}

static inline irq_flags_t irq_bios_flags_get(void) {
#ifdef ARM7
	return ROM_IRQ_CHECKFLG | ((uint64_t)ROM_IRQ_CHECKFLG2 << 32);
#elif defined(ARM9)
	uintptr_t addr = (cp15_dtcm_get_base() & 0xfffff000) + ROM_IRQ_CHECKFLG_OFF;
	return *(irq_flags_t*)addr;
#endif
}
static inline irq_flags_t irq_bios_flags_set(irq_flags_t flags) {
	irq_flags_t r;
#ifdef ARM7
	r = ROM_IRQ_CHECKFLG | ((uint64_t)ROM_IRQ_CHECKFLG2 << 32);
	ROM_IRQ_CHECKFLG = flags;
	ROM_IRQ_CHECKFLG2= flags >> 32;
#elif defined(ARM9)
	uintptr_t addr = (cp15_dtcm_get_base() & 0xfffff000) + ROM_IRQ_CHECKFLG_OFF;
	r = *(irq_flags_t*)addr;
	*(irq_flags_t*)addr = flags;
#endif
	return r;
}

static inline irq_flags_t irq_pending_get_all(void) {
	return irq_enable_get() & irq_flags_get();
}
static inline void irq_acknowledge(irq_flags_t flags) {
	irq_flags_set(flags);
	irq_bios_flags_set(irq_bios_flags_get() | flags);
}

#endif

