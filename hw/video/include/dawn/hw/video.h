
#ifndef DAWN_HW_VIDEO_H_
#define DAWN_HW_VIDEO_H_

#include <stdint.h>

#include <dawn/hw/video/regs.h>


static inline uint16_t video_get_vcount_cmp(void) {
	uint16_t v = REG_DISPSTAT;
	return (v >> 8) | ((v & 0x80) << 1);
}

#endif

