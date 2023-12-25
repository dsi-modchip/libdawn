
#ifndef DAWN_HW_DMA_H_
#define DAWN_HW_DMA_H_

#include <dawn/hw/arm.h>

#include <dawn/hw/dma/struct.h>

static inline bool dma_is_busy(int channel) {
	return REG_DMA_HW(channel).cnt & REG_DMA_CNT_ENABLE_Msk;
}
static inline void dma_wait_finish_blocking(int channel) {
	while (dma_is_busy(channel)) {
		COMPILER_BARRIER();
	}
}
static inline void dma_force_stop(int channel) {
	REG_DMA_HW(channel).cnt &= ~(uint16_t)REG_DMA_CNT_ENABLE_Msk;
}

// TODO: init routines?

#endif

