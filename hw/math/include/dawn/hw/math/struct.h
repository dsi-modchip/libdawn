
#ifndef DAWN_HW_MATH_STRUCT_H_
#define DAWN_HW_MATH_STRUCT_H_

#ifndef ARM9
#error "Math accelerator is exclusive to the ARM9!"
#endif

#include <stdint.h>

#include <dawn/hw/iobase.h>


struct math_hw {
	uint32_t divcnt;
	uint32_t _pad[3];
	 int64_t div_numer;
	 int64_t div_denom;
	 int64_t div_result;
	 int64_t divrem_result;

	uint32_t sqrtcnt;
	uint32_t sqrt_result;
	uint64_t sqrt_param;
};

enum math_div_mode {
	math_div_32d32 = 0,
	math_div_64d32 = 1,
	math_div_64d64 = 2
};

enum math_sqrt_mode {
	math_sqrt_32bit = 0,
	math_sqrt_64bit = 1
};

#define REG_MATH_HW (*(volatile struct math_hw*)IO_MATH_BASE)

#endif

