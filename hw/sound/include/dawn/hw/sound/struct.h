
#ifndef DAWN_HW_SOUND_STRUCT_H_
#define DAWN_HW_SOUND_STRUCT_H_

#ifndef ARM7
#error "The sound hardware is exclusive to the ARM7!"
#endif


#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <dawn/hw/iobase.h>

struct sound_hw_channel {
	uint32_t cnt;
	uint32_t sad;
	uint16_t tmr;
	uint16_t pnt;
	uint32_t len;
};

struct sound_hw_capture {
	uint8_t cnt0;
	uint8_t cnt1;
	uint8_t _pad[6];
	uint32_t dad0;
	uint32_t len0;
	uint32_t dad1;
	uint32_t len1;
};

struct sound_hw {
	struct sound_hw_channel channel[16];
	uint32_t cnt;
	uint32_t bias;
	struct sound_hw_capture capture;
};
static_assert(offsetof(struct sound_hw, capture) == 0x508, "Struct declaration is wrong!");


#define REG_SOUND_HW (*(volatile struct sound_hw*)IO_SOUND_BASE)

#endif

