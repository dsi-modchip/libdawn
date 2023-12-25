
#ifndef DAWN_HW_ROM_NTR7_H_
#define DAWN_HW_ROM_NTR7_H_

#include <dawn/hw/rom/common7.h>


static inline void swi_SoftReset(void) { // 00
	ARM_SWI0(0x00);
}
static inline bool swi_IsDebugger() { // 0f
	return ARM_SWI0(0x0f);
}

#endif

