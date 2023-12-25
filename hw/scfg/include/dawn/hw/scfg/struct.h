
#ifndef DAWN_HW_SCFG_STRUCT_H_
#define DAWN_HW_SCFG_STRUCT_H_

#include <dawn/hw/iobase.h>

#ifdef ARM7
struct scfg_hw {
	uint16_t rom;
	uint16_t romwe;
	uint16_t clk;
	uint16_t jtag;
	uint32_t ext;
	uint32_t _unk0;
	uint16_t mc;
	uint16_t card_insert_delay;
	uint16_t card_pwroff_delay;
	uint16_t _unk1[5]; // 16, 18, 1a, 1c, 1e
	uint32_t wl;
	uint32_t op;
};
#elif defined(ARM9)
struct scfg_hw {
	uint16_t rom;
	uint16_t romwe;
	uint16_t clk;
	uint16_t rst;
	uint32_t ext;
	uint32_t _unk0;
	const uint16_t mc;
};
#else
#error "Need either ARM7 or ARM9 defined!"
#endif

#define REG_SCFG_HW (*(volatile struct scfg_hw*)IO_SCFG_BASE)

#endif

