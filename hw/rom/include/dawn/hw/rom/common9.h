
#ifndef DAWN_HW_ROM_NTR9_H_
#define DAWN_HW_ROM_NTR9_H_

#ifndef ARM9
#error "This file is ARM9-only!"
#endif

#include <dawn/hw/rom/common.h>


static inline void swi_Diff8bitUnFilterWrite8bit(const struct swi_Compr_Header* src, void* dst) { // 16
	ARM_SWI2(0x16, src, dst);
}
static inline void swi_Diff16bitUnFilter(const struct swi_Compr_Header* src, void* dst) { // 18
	ARM_SWI2(0x18, src, dst);
}
static inline void swi_CustomPost(uint32_t postflg) { // 1f
	ARM_SWI1(0x1f, postflg);
}

#endif

