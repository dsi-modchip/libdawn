
#ifndef DAWN_HW_INPUT_H_
#define DAWN_HW_INPUT_H_

#include <stdbool.h>

#include <dawn/hw/input/regs.h>
#include <dawn/hw/input/struct.h>


enum input_keys {
	input_key_a      = 0,
	input_key_b      = 1,
	input_key_select = 2,
	input_key_start  = 3,
	input_key_right  = 4,
	input_key_left   = 5,
	input_key_up     = 6,
	input_key_down   = 7,
	input_key_r      = 8,
	input_key_l      = 9,

#ifdef ARM7
	input_key_x     = 0+16,
	input_key_y     = 1+16,
	input_key_debug = 3+16,
	input_key_pen   = 6+16,
	input_key_hinge = 7+17,
#endif
};


static inline bool input_key_is_pressed(enum input_keys key) {
	bool k = !(REG_KEY_HW.keyinput & (1 << key));
#ifdef ARM7
	if (key < 16) {
		return k;
	} else {
		bool r = REG_KEY_HW.extkeyin & (1 << (key-16));
		return (key < input_key_hinge) ? !r : r;
	}
#elif defined(ARM9)
	return k;
#endif
}
static inline uint32_t input_key_is_pressed_mask(uint32_t mask) {
	uint32_t r = 0;

	r |= (uint16_t)((~REG_KEY_HW.keyinput) & mask);
#ifdef ARM7
	r |= ((0x007f & ~REG_KEY_HW.extkeyin) | (0xff80 & REG_KEY_HW.extkeyin)) & (mask >> 16);
#endif

	return r;
}

#endif

