
#ifndef DAWN_HW_ROM_COMMON7_H_
#define DAWN_HW_ROM_COMMON7_H_

#ifndef ARM7
#error "This file is ARM7-only!"
#endif

#include <dawn/hw/rom/common.h>


enum swi_CustomHalt_Flags {
	swi_CustomHalt_Halt  = 0x80,
	swi_CustomHalt_Sleep = 0xc0,
};


/** @brief short for swi_CustomHalt(swi_CustomHalt_Sleep) */
static inline void swi_Sleep() { // 07
	ARM_SWI3(0x07, DONT_CARE(uint32_t), DONT_CARE(uint32_t), DONT_CARE(uint32_t));
}
static inline void swi_SoundBias(int level, int delay) { // 08
	ARM_SWI2(0x08, level, delay);
}
static inline uint16_t swi_GetSineTable(int idx) { // 1a
	return ARM_SWI1(0x1a, idx);
}
uint16_t swi_GetPitchTable(int idx); // 1b // bugged in TWL BIOS
static inline uint8_t swi_GetVolumeTable(int idx) { // 1c
	return ARM_SWI1(0x1c, idx);
}
/*static inline void swi_GetBootProcs() { // 1d
}*/
static inline void swi_CustomHalt(enum swi_CustomHalt_Flags flags) { // 1f
	ARM_SWI3(0x1f, DONT_CARE(uint32_t), DONT_CARE(uint32_t), flags);
}

#endif

