
#ifndef DAWN_HW_DMA_STRUCT_H_
#define DAWN_HW_DMA_STRUCT_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/iobase.h>

#include <dawn/hw/dma/regs.h>

struct dma_hw {
	uint32_t sad;
	uint32_t dad;
	uint16_t wcnt;
	uint16_t cnt;
};

#define REG_DMA_HW(x) (*(volatile struct dma_hw*)REG_DMA_SAD_ADDR(x))

enum dma_cnt_srcdst {
	dma_cnt_srcdst_inc = 0,
	dma_cnt_srcdst_dec = 1,
	dma_cnt_srcdst_fix = 2,
	dma_cnt_dst_reload = 3,
};

#ifdef ARM9
enum dma_cnt_mode {
	dma_cnt_mode_immediate = 0,
	dma_cnt_mode_vblank = 1,
	dma_cnt_mode_hblank = 2,
	dma_cnt_mode_dispstart = 3,
	dma_cnt_mode_dramdisp = 4,
	dma_cnt_mode_ntrcart = 5,
	dma_cnt_mode_agbcart = 6,
	dma_cnt_mode_gxfifo = 7
};

static inline volatile uint32_t* dma_fill_from_channel(
		volatile struct dma_hw* dmach) {
	size_t chno = dmach - &REG_DMA_HW(0);
	return &REG_DMA_FDATA(chno);
}
#elif defined(ARM7)
enum dma_cnt_mode {
	dma_cnt_mode_immediate = 0,
	dma_cnt_mode_vblank    = 2,
	dma_cnt_mode_ntrcart   = 4,
	dma_cnt_mode_nwmirq    = 6, /**< channels 0 and 2 only */
	dma_cnt_mode_agbcart   = 6, /**< channels 1 and 3 only */
};
#endif

static inline uint16_t dma_cnt_make(enum dma_cnt_srcdst dstctl,
		enum dma_cnt_srcdst srcctl, bool repeat, bool is32bit,
		enum dma_cnt_mode mode, bool ie, bool enable) {
	return (dstctl << REG_DMA_CNT_DSTCTL_Lsb)
		 | (srcctl << REG_DMA_CNT_SRCCTL_Lsb)
		 | ((repeat?1:0) << REG_DMA_CNT_REPEAT_Lsb)
		 | ((is32bit?1:0)<< REG_DMA_CNT_32BIT_Lsb)
		 | (mode << REG_DMA_CNT_MODE_Lsb)
		 | ((ie?1:0) << REG_DMA_CNT_IE_Lsb)
		 | ((enable?1:0) << REG_DMA_CNT_ENABLE_Lsb)
	;
}

#endif

