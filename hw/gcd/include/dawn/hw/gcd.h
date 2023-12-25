
#ifndef DAWN_HW_GCD_H_
#define DAWN_HW_GCD_H_

#include <dawn/hw/gcd/regs.h>
#include <dawn/hw/gcd/struct.h>

static inline volatile uint32_t* gcd_romresp_from_hw(volatile struct gcd_hw* gcd) {
	if (hw == &REG_GCD2_HW) {
		return &REG_ROMRESP2;
	} else {
		return &REG_ROMRESP;
	}
}

static inline void gcd_set_key1seed(volatile struct gcd_hw* gcd, int slot, uint64_t seed) {
	slot &= 1;
	*(&(gcd->key1seed0l) + slot) = seed;
	*(&(gcd->key1seed0h) + slot) = seed >> 32;
}

#endif

