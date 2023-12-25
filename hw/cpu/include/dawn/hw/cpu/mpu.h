
#ifndef DAWN_HW_CPU_MPU_H_
#define DAWN_HW_CPU_MPU_H_

#ifndef ARM9
#error "The MPU is exclusive to the ARM9."
#endif

#include <dawn/hw/cpu/cp15.h>

static inline bool mpu_is_enabled(void) {
	return (cp15_control_get() & cp15_ctl_mpu_enable) != 0;
}
static inline bool mpu_enable(bool enable) {
	return cp15_control_set_masked((enable ? cp15_ctl_mpu_enable : 0), cp15_ctl_mpu_enable);
}

enum mpu_flags {
	mpu_flag_enable = 1<<0,
	mpu_flag_icache = 1<<1,
	mpu_flag_dcache = 1<<2,
	// write-back (else write-through)
	mpu_flag_dc_wb  = 1<<3,

	// unprivileged access bits
	mpu_flag_u_r = 1<< 8,
	mpu_flag_u_w = 1<< 9,
	mpu_flag_u_x = 1<<10,
	// privileged access bits
	mpu_flag_p_r = 1<<11,
	mpu_flag_p_w = 1<<12,
	mpu_flag_p_x = 1<<13,
};

enum mpu_region_size {
	mpu_region_4k = 11,
	mpu_region_8k = 12,
	mpu_region_16k = 13,
	mpu_region_32k = 14,
	mpu_region_64k = 15,
	mpu_region_128k = 16,
	mpu_region_256k = 17,
	mpu_region_512k = 18,
	mpu_region_1M = 19,
	mpu_region_2M = 20,
	mpu_region_4M = 21,
	mpu_region_8M = 22,
	mpu_region_16M = 23,
	mpu_region_32M = 24,
	mpu_region_64M = 25,
	mpu_region_128M = 26,
	mpu_region_256M = 27,
	mpu_region_512M = 28,
	mpu_region_1G = 29,
	mpu_region_2G = 30,
	mpu_region_4G = 31
};

uint32_t mpu_dcache_bits_get(void);
uint32_t mpu_dcache_bits_set(uint32_t v);
uint32_t mpu_dcache_bits_set_masked(uint32_t v, uint32_t mask);

uint32_t mpu_icache_bits_get(void);
uint32_t mpu_icache_bits_set(uint32_t v);
uint32_t mpu_icache_bits_set_masked(uint32_t v, uint32_t mask);

uint32_t mpu_dcache_wrbuf_bits_get(void);
uint32_t mpu_dcache_wrbuf_bits_set(uint32_t v);
uint32_t mpu_dcache_wrbuf_bits_set_masked(uint32_t v, uint32_t mask);

uint32_t mpu_accperm_i_get(void);
uint32_t mpu_accperm_i_set(uint32_t v);
uint32_t mpu_accperm_i_set_masked(uint32_t v, uint32_t mask);

uint32_t mpu_accperm_d_get(void);
uint32_t mpu_accperm_d_set(uint32_t v);
uint32_t mpu_accperm_d_set_masked(uint32_t v, uint32_t mask);

// RASR? RBAR?
uint32_t mpu_region_info_get(int region);
uint32_t mpu_region_info_set(int region, uint32_t v);
uint32_t mpu_region_info_set_masked(int region, uint32_t v, uint32_t mask);

/**
 * @param ic_dc_wb icacheable, dcacheable and wrbufferable bits: bitflag for
 *                 every region (out of 8), lowest byte is icacheability,
 *                 mid byte is dcacheability, high byte is wrbufferability
 * @param iap instruction access permissions, one nybble per MPU region (out of
 *            8). for possible values, see https://problemkaputt.de/gbatek-arm-cp15-protection-unit-pu.htm
 * @param dap data access permissions, one nybble per MPU region (out of 8).
 *            for possible values, see https://problemkaputt.de/gbatek-arm-cp15-protection-unit-pu.htm
 * @param regnfo pointer to an array of 8 32-bit words, one per region,
 *               denoting the base address, size, and enable bit of this
 *               region. for the format, use `mpu_regnfo_make`.
 */
uint32_t mpu_initialize_full(uint32_t ic_dc_wb, uint32_t iap, uint32_t dap, const uint32_t regnfo[static 8]);

enum mpu_flags mpu_region_get_flags(int region);
void mpu_region_set_props(int region, uintptr_t base, enum mpu_region_size size,
		enum mpu_flags flags);


static inline uintptr_t mpu_regnfo_get_base(uint32_t regnfo) {
	return regnfo & ~(uint32_t)0xff;
}
static inline enum mpu_region_size mpu_regnfo_get_size(uint32_t regnfo) {
	return (regnfo & 0xfe) >> 1;
}
static inline bool mpu_regnfo_get_enable(uint32_t regnfo) {
	return regnfo & 1;
}
static inline uint32_t mpu_regnfo_make(uintptr_t base, enum mpu_region_size size, bool en) {
	return base | (size << 1) | (en ? 1 : 0);
}

static inline uintptr_t mpu_region_get_base(int region) {
	return mpu_regnfo_get_base(mpu_region_info_get(region));
}
static inline enum mpu_region_size mpu_region_get_size(int region) {
	return mpu_regnfo_get_size(mpu_region_info_get(region));
}
static inline bool mpu_region_get_enable(int region) {
	return mpu_regnfo_get_enable(mpu_region_info_get(region));
}

#endif

