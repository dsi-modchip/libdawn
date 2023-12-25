
#ifndef DAWN_HW_ROM_TWL7_H_
#define DAWN_HW_ROM_TWL7_H_

#include <dawn/hw/rom/common7.h>
#include <dawn/hw/rom/twlcrypt.h>


static inline void swi_LZ77UnCompReadByCallbackWrite8bit(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs) { // 01
	ARM_SWI4(0x01, src, dst, ud, cbs);
}

#endif

