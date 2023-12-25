
#ifndef DAWN_HW_DBG_STRUCT_H_
#define DAWN_HW_DBG_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

struct dbg_nocash_hw {
	const char emulator_id[16];
	volatile void* str_out;
	volatile void* str_format;
	volatile void* str_format_lf;
	uint32_t chr_out;
	const uint64_t clock_cycs;
};

#define REG_DBG_NOCASH_HW (*(volatile struct dbg_nocash_hw*)IO_DBG_NOCASH_BASE)

#endif

