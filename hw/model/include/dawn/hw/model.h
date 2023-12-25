
#ifndef DAWN_HW_MODEL_H_
#define DAWN_HW_MODEL_H_

#include <stddef.h>
#include <stdbool.h>


enum dawn_hw_model_type {
	dawn_hw_model_debug_flag = 0x80, /**< double RAM size */

	dawn_hw_model_ntr = 0, /**< DS phat/lite */
	dawn_hw_model_twl = 1, /**< DSi/XL, running in TWL mode */
	dawn_hw_model_twl_ntrmode = 2, /**< DSi/XL, running in NTR mode */
	//dawn_hw_model_ctr_twlmode = 8, /**< (N)3DS, running in TWL mode */ // TODO: needs detection via I2C

	dawn_hw_model_model_mask = 0x7f,
};


enum dawn_hw_model_type dawn_hw_model_get(void);

static inline bool dawn_hw_model_is_twl_mode(void) {
	return (dawn_hw_model_get() & dawn_hw_model_model_mask) == dawn_hw_model_twl;
}
static inline bool dawn_hw_model_has_slot2(void) {
	return (dawn_hw_model_get() & dawn_hw_model_model_mask) == dawn_hw_model_ntr;
}

static inline size_t dawn_hw_model_get_dram_mb(enum dawn_hw_model_type model) {
	size_t r;

	if ((model & dawn_hw_model_model_mask) == dawn_hw_model_twl) r = 16; // 16 MiB
	else r = 4; // 4 MiB

	if (model & dawn_hw_model_debug_flag) r <<= 1;

	return r;
}

#endif

