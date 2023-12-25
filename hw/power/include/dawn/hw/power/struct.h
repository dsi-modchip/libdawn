
#ifndef DAWN_HW_POWER_STRUCT_H_
#define DAWN_HW_POWER_STRUCT_H_

#include <dawn/hw/iobase.h>
#include <dawn/hw/power/regs.h>


#ifdef ARM7
struct power_hw {
	uint8_t postflg;
	uint8_t haltcnt;
	uint16_t _pad;
	union {
		uint8_t powcnt;
		uint8_t powcnt2;
	};
};
#elif defined(ARM9)
struct power_hw {
	uint8_t postflg;
	uint8_t _pad[3];
	union {
		uint16_t powcnt;
		uint16_t powcnt1;
	};
};
#endif


#define REG_POWER_HW (*(volatile struct power_hw*)IO_POWER_BASE)

#endif

