
#ifndef DAWN_HW_USG_STRUCT_H_
#define DAWN_HW_USG_STRUCT_H_

#include <stdio.h>

#include <dawn/hw/iobase.h>


struct usg_hw {
	uint16_t regcnt;
	uint16_t _pad0[7];
	uint16_t dispcnt2;
	uint16_t _pad1[7];
	uint16_t dispsw;
	uint16_t _pad2[7];
	uint16_t clk11m;
};


#define REG_USG_HW (*(volatile struct usg_hw*)IO_USG_BASE)

#endif

