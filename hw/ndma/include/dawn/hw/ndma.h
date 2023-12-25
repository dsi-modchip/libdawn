
#ifndef DAWN_HW_NDMA_H_
#define DAWN_HW_NDMA_H_

#include <stdbool.h>

#include <dawn/hw/ndma/struct.h>

static inline bool ndma_is_busy(int channel) {
	return REG_NDMA_HW.ch[channel].cnt & REG_NDMACNT_ENABLE_Msk;
}
static inline void ndma_wait_finish_blocking(int channel) {
	while (ndma_is_busy(channel)) {
		COMPILER_BARRIER();
	}
}
static inline void ndma_force_stop(int channel) {
	REG_NDMA_HW.ch[channel].cnt &= ~(uint32_t)REG_NDMACNT_ENABLE_Msk;
}

// TODO: init routines?

#endif

