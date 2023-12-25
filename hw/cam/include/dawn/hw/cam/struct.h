
#ifndef DAWN_HW_CAM_REGS_H_
#define DAWN_HW_CAM_REGS_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

#if ARM9
struct cam_hw {
	uint16_t mcnt;
	uint16_t cnt;
	uint32_t dat;
	uint64_t _pad;
	uint32_t sofs;
	uint32_t eofs;
};

#define REG_CAM_HW (*(volatile struct cam_hw*)IO_CAM_BASE)
#endif

#endif

