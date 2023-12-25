
#ifndef DAWN_HW_NDMA_STRUCT_H_
#define DAWN_HW_NDMA_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/ndma/regs.h>


struct ndma_ch {
	uint32_t sad;
	uint32_t dad;
	uint32_t tcnt;
	uint32_t wcnt;
	uint32_t bcnt;
	uint32_t fdata;
	uint32_t cnt;
};

struct ndma_hw {
	uint32_t gcnt;
	struct ndma_ch ch[4];
};

#define REG_NDMA_HW (*(volatile struct ndma_hw*)IO_NDMA_BASE)


#endif

