
#ifndef DAWN_BAREMETALRT_ABI_TWL_HIRAM_H_
#define DAWN_BAREMETALRT_ABI_TWL_HIRAM_H_

#include <dawn/baremetal-rt/abi/ntr_hiram.h>
#include <dawn/baremetal-rt/abi/hb_transferregion.h>


struct __attribute__((__packed__)) twl_emmc_info {
	uint8_t cid[16];
	uint8_t csd[16];
	uint32_t ocr;
	uint64_t scr;
	uint16_t rca;
	uint16_t typ; /**< 0=sdmc 1=emmc */
	uint16_t hcs;
	uint16_t _reserved_0[3];
	uint32_t csr;
	uint16_t clkctl;
	uint16_t option;
	uint16_t _reserved_1;
	uint16_t device; /**< 0=sdmc 1=emmc */
};
static_assert(sizeof(struct twl_emmc_info) == 0x800-0x7bc);


struct __attribute__((__packed__)) twl_hiram {
	struct cartridge_twl twl_a;
	uint8_t _zero_0[0x7b0];
	char verdata_name[8+1];
	char verdata_region;
	uint16_t _reserved_0;
	struct twl_emmc_info emmc;
	struct title_list title_list;
	uint8_t _zero_1[0x400];
	struct cartridge_twl twl_b;
	struct hb_transfer_region transfer_region;
	uint8_t _reserved_1[0xc00-0x1c];
	struct ntr_hiram ntr;
};
static_assert(offsetof(struct twl_hiram, title_list) == 0x1800);
static_assert(offsetof(struct twl_hiram, twl_b) == 0x2000);
static_assert(offsetof(struct twl_hiram, transfer_region) == 0x3000);
static_assert(offsetof(struct twl_hiram, ntr) == 0x3c00);
static_assert(sizeof(struct twl_hiram) == 0x4000);

#define ABI_TWL_HIRAM ((volatile struct twl_hiram*)0x02ffc000)

#endif

