
#ifndef DAWN_HW_NWRAM_H_
#define DAWN_HW_NWRAM_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/nwram/regs.h>
#include <dawn/hw/nwram/struct.h>

/**
 * @param bank 0, 1 or 2 (NWRAM-A, -B or -C)
 * @param bus CPU bus to attach to (ARM7, ARM9, DSP-code, or DSP-data)
 * @param vstart 'virtual' start address (which address the NWRAM should be mapped at)
 * @param vend 'virtual' end address (which address the NWRAM should be mapped at)
 * @param poff 'physical' offset (which slot(s) to use as backing memory)
 * @param psize 'physical' size (how many slots to use)
 */
static inline bool nwram_map(int bank, enum nwram_bus bus,
		uintptr_t vstart, uintptr_t vend,
		size_t poff, size_t psize) {
	if (bank < 0 || bank >= 3) return false;
	if (vstart < WRAM_BASE || vstart >= IO_BASE) return false;
	if (vend < WRAM_BASE || vend >= IO_BASE) return false;
	if (vend < vstart) return false;

	int isz;
	int slotstart, nslots;
	volatile uint8_t* ptr;
	int en = (vend != vstart && psize >= 32*1024) ? REG_MBK_ALLOC_EN_Msk : 0;

	if (psize >= 256*1024) isz = 3;
	else if (psize >= 128*1024) isz = 2;
	else if (psize >= 64*1024) isz = 1;
	else /*if (psize >= 32*1024)*/ isz = 0;

	if (bank == 0) {
		slotstart = poff >> 16;
		nslots = psize >> 16;
		ptr = &REG_NWRAM_HW.alloc_a;

		if (slotstart >= 4 || nslots > 4 || nslots+slotstart >= 4) return false;
	} else {
		slotstart = poff >> 15;
		nslots = psize >> 15;
		ptr = (bank == 2) ? &REG_NWRAM_HW.alloc_c : &REG_NWRAM_HW.alloc_b;

		if (slotstart >= 8 || nslots > 8 || nslots+slotstart >= 8) return false;
	}

	REG_NWRAM_HW.map[bank]
		= (((vstart >> 15) << REG_MBK_MAP_START_Lsb) & REG_MBK_MAP_START_Msk)
		| (isz << REG_MBK_MAP_SIZE_Lsb)
		| (((vend >> 15) << REG_MBK_MAP_END_Lsb) & REG_MBK_MAP_END_Msk);

	for (int i = 0; i < nslots; ++i) {
		ptr[i + slotstart]
			= ((bus << REG_MBK_ALLOC_BUS_Lsb) & REG_MBK_ALLOC_BUS_Msk)
			| (((i + slotstart) << REG_MBK_ALLOC_OFF_Lsb) & REG_MBK_ALLOC_OFF_Msk)
			| en;
	}
}

#endif

