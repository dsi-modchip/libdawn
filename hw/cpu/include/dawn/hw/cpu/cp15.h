
#ifndef DAWN_HW_CPU_CP15_H_
#define DAWN_HW_CPU_CP15_H_

#ifndef ARM9
#error "The CP15 is exclusive to the ARM9."
#endif

#include <stddef.h>
#include <stdbool.h>

#include <dawn/hw/arm.h>

CONST_FN uint32_t cp15_get_main_id(void);

CONST_FN uint32_t cp15_get_cache_info(void);
CONST_FN uint32_t cp15_get_tcm_info(void);

static inline size_t cp15_get_itcm_size(void) {
	uint32_t r = cp15_get_tcm_info();
	r = (r >>  6) & 0xf;
	return (r == 0) ? 0 : (512u << r);
}
static inline uint32_t cp15_get_dtcm_size(void) {
	uint32_t r = cp15_get_tcm_info();
	r = (r >> 18) & 0xf;
	return (r == 0) ? 0 : (512u << r);
}

enum cp15_control {
	cp15_ctl_mpu_enable        = 1<< 0,
//	cp15_ctl_fault_on_misalign = 1<< 1, // always 0
	cp15_ctl_dcache_enable     = 1<< 2,
	cp15_ctl_wrbuf_enable      = 1<< 3,
//	cp15_ctl_exn_handle_32bit  = 1<< 4, // always 1
//	cp15_ctl_disable_26bit     = 1<< 5, // always 1
//	cp15_ctl_use_v4_abrt_model = 1<< 6, // always 1
	cp15_ctl_big_endian        = 1<< 7,
//	cp15_ctl_mmu_sysprot       = 1<< 8, // always 0
//	cp15_ctl_mmu_romprot       = 1<< 9, // always 0
//	cp15_ctl_impldef           = 1<<10, // always 0
//	cp15_ctl_branch_predict    = 1<<11, // always 0
	cp15_ctl_icache_enable     = 1<<12,
	cp15_ctl_exn_vector_hi     = 1<<13, /**< 1=map vtor at 0xffff0000, 0=at 0 */
	cp15_ctl_cacherepl_rrobin  = 1<<14, /**< 0=random replace, 1=round-robin */
	/** 1=pre-ARMv5-behavior of ldm/ldr/pop wrt thumb bit, 0=ARMv5 and up
	 * ARMv4 and lower: doesn't change thumb mode on ldm/ldr
	 * ARMv5 and up: is able to change thumb mode on ldm/ldr (if pc is destreg)
	 */
	cp15_ctl_ldmldr_pre_v5     = 1<<15,
	cp15_ctl_dtcm_enable       = 1<<16,
	cp15_ctl_dtcm_loadmode     = 1<<17, /**< "load mode" means "write-only" */
	cp15_ctl_itcm_enable       = 1<<18,
	cp15_ctl_itcm_loadmode     = 1<<19, /**< "load mode" means "write-only" */
//	cp15_ctl_unalign_acc_enable= 1<<22, // always 0
//	cp15_ctl_ext_pagetbl_disable=1<<23, // always 0
//	cp15_ctl_cpsr_e_on_exn     = 1<<25, // always 0
//	cp15_ctl_fiq_nonmaskable   = 1<<27, // always 0
//	cp15_ctl_tex_reg_remap     = 1<<28, // always 0
//	cp15_ctl_mmu_force_apbit   = 1<<29, // always 0
};

enum cp15_control cp15_control_get(void);
enum cp15_control cp15_control_set(enum cp15_control ctl);
enum cp15_control cp15_control_set_masked(enum cp15_control ctl, enum cp15_control mask);

uint32_t cp15_dtcm_get_info(void);
uint32_t cp15_itcm_get_info(void);

static inline uintptr_t cp15_dtcm_get_base(void) {
	return cp15_dtcm_get_info() & ~(uint32_t)((1u<<12)-1);
}
static inline size_t cp15_dtcm_get_vsize(void) {
	uint32_t vsz = cp15_dtcm_get_info() & (uint32_t)((1u<<12)-1);
	return 512ul << (vsz >> 1);
}
static inline size_t cp15_itcm_get_vsize(void) {
	uint32_t vsz = cp15_itcm_get_info() & (uint32_t)((1u<<12)-1);
	return 512ul << (vsz >> 1);
}

uint32_t cp15_dtcm_set_info(uint32_t info);
uint32_t cp15_itcm_set_info(uint32_t info);

static inline uint32_t cp15_tcm__size_to_n(size_t size) {
	return (uint32_t)(-__builtin_clzl(size) + 23);
}

static inline uint32_t cp15_dtcm_set_base_vsize(uintptr_t base, size_t size) {
	uint32_t b = (uint32_t)base & ~(uint32_t)((1u<<12)-1);
	uint32_t vsz = cp15_tcm__size_to_n(size);
	return cp15_dtcm_set_info(b | vsz);
}
static inline size_t cp15_itcm_set_vsize(size_t size) {
	return 512ul << (cp15_itcm_set_info(cp15_tcm__size_to_n(size)) >> 1);
}
static inline size_t cp15_dtcm_set_vsize(size_t size) {
	uint32_t m = (uint32_t)((1u<<12)-1);
	uint32_t b = cp15_dtcm_get_info() & ~m;
	uint32_t r = cp15_dtcm_set_base_vsize(b, size);
	return 512ul << ((r & m) >> 1);
}
uintptr_t cp15_dtcm_set_base(uintptr_t base) {
	uint32_t m = (uint32_t)((1u<<12)-1);
	uint32_t n = cp15_dtcm_get_info() & m;
	uint32_t r = cp15_dtcm_set_info(((uint32_t)base & ~m) | n);
	return r & ~m;
}

void cp15_wfi(void);

uint32_t cp15_get_etmprocid(void);
uint32_t cp15_set_etmprocid(uint32_t v);

#endif

