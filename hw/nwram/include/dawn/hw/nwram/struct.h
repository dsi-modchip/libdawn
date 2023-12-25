
#ifndef DAWN_HW_NWRAM_STRUCT_H_
#define DAWN_HW_NWRAM_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>


struct nwram_hw {
	union {
		struct {
			uint32_t mbk1, mbk2, mbk3, mbk4, mbk5;
		};
		struct {
			uint8_t mbk10, mbk11, mbk12, mbk13;
			uint8_t mbk20, mbk21, mbk22, mbk23;
			uint8_t mbk30, mbk31, mbk32, mbk33;
			uint8_t mbk40, mbk41, mbk42, mbk43;
			uint8_t mbk50, mbk51, mbk52, mbk53;
		};
		uint8_t alloc[5*4];
		struct {
			uint8_t alloc_a[4];
			uint8_t alloc_b[8];
			uint8_t alloc_c[8];
		};
	};

	union {
		struct {
			uint32_t mbk6, mbk7, mbk8;
		};
		uint32_t map[3];
		struct {
			uint32_t map_a, map_b, map_c;
		};
	};

	uint32_t prot;
};

enum nwram_bus {
	nwram_bus_arm9 = 0,
	nwram_bus_arm7 = 1,
	nwram_bus_dspi = 2,
	nwram_bus_dspd = 3
};


#define REG_NWRAM_HW (*(struct nwram_hw*)IO_NWRAM_BASE)

#endif

