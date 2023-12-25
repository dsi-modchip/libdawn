
#ifndef DAWN_HW_MATH_H_
#define DAWN_HW_MATH_H_

#include <dawn/hw/arm.h>

#include <dawn/hw/math/regs.h>
#include <dawn/hw/math/struct.h>

static inline int32_t math_div_32d32_blocking(int32_t numer, int32_t denom) {
	REG_MATH_HW->div_numer = numer;
	REG_MATH_HW->div_denom = denom;
	REG_MATH_HW->divcnt = math_div_32d32;
	while (REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->div_result;
}
static inline int64_t math_div_64d32_blocking(int64_t numer, int32_t denom) {
	REG_MATH_HW->div_numer = numer;
	REG_MATH_HW->div_denom = denom;
	REG_MATH_HW->divcnt = math_div_64d32;
	while (REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->div_result;
}
static inline int64_t math_div_64d64_blocking(int64_t numer, int64_t denom) {
	REG_MATH_HW->div_numer = numer;
	REG_MATH_HW->div_denom = denom;
	REG_MATH_HW->divcnt = math_div_64d64;
	while (REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->div_result;
}

static inline int32_t math_rem_32d32_blocking(int32_t numer, int32_t denom) {
	REG_MATH_HW->div_numer = numer;
	REG_MATH_HW->div_denom = denom;
	REG_MATH_HW->divcnt = math_div_32d32;
	while (REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->divrem_result;
}
static inline int32_t math_rem_64d32_blocking(int64_t numer, int32_t denom) {
	REG_MATH_HW->div_numer = numer;
	REG_MATH_HW->div_denom = denom;
	REG_MATH_HW->divcnt = math_div_64d32;
	while (REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->divrem_result;
}
static inline int64_t math_rem_64d64_blocking(int64_t numer, int64_t denom) {
	REG_MATH_HW->div_numer = numer;
	REG_MATH_HW->div_denom = denom;
	REG_MATH_HW->divcnt = math_div_64d64;
	while (REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->divrem_result;
}

static inline uint32_t math_sqrt_32_blocking(uint32_t x) {
	REG_MATH_HW->sqrt_param = x;
	REG_MATH_HW->sqrtcnt = math_sqrt_32bit;
	while (REG_MATH_HW->sqrtcnt & REG_SQRTCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->sqrt_result;
}
static inline uint32_t math_sqrt_64_blocking(uint64_t x) {
	REG_MATH_HW->sqrt_param = x;
	REG_MATH_HW->sqrtcnt = math_sqrt_64bit;
	while (REG_MATH_HW->sqrtcnt & REG_SQRTCNT_BUSY_Msk) COMPILER_BARRIER();
	return REG_MATH_HW->sqrt_result;
}


static inline void math_irq_save(struct math_hw* backup) {
	*backup = REG_MATH_HW;
}
static inline void math_irq_restore(struct math_hw* backup) {
	REG_MATH_HW = *backup;
	while ((REG_MATH_HW->divcnt & REG_DIVCNT_BUSY_Msk) || (REG_MATH_HW->sqrtcnt & REG_SQRTCNT_BUSY_Msk))
		COMPILER_BARRIER();
}

#endif

