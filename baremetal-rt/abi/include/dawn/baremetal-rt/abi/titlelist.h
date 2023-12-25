
#ifndef DAWN_BAREMETALRT_ABI_TITLELIST_H_
#define DAWN_BAREMETALRT_ABI_TITLELIST_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>


struct __attribute__((__packed__)) title_id {
	union {
		uint64_t value;
		struct {
			char emagcode[4];
			uint8_t filetype;
			uint8_t tid_rvl;
			uint8_t tid_twl;
			uint8_t tid_ctr;
		};
	};
};
static_assert(sizeof(struct title_id) == 8);


struct __attribute__((__packed__)) title_list {
	uint8_t title_count;
	uint8_t _reserved[15];
	uint64_t flags_pub[2]; /**< same makercode and public.sav */
	uint64_t flags_prv[2]; /**< same makercode and private.sav */
	uint64_t flags_jmp[2]; /**< jumpable/current (cf cart header flags) */
	uint64_t flags_mkr[2]; /**< same makercode */
	struct title_id tids[118];
};
static_assert(offsetof(struct title_list, tids) == 0x50);

#define ABI_TITLE_LIST ((struct title_list*)0x02ffd800)

#endif

