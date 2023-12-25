
#ifndef DAWN_BAREMETALRT_ABI_HB_TRANSFERREGION_H_
#define DAWN_BAREMETALRT_ABI_HB_TRANSFERREGION_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>

#include <dawn/baremetal-rt/abi/hb_bootstub.h>

/** the 'transfer region' is a small region of memory used to forward a few
 * variables between the two cores in libnds. it is typically found at
 * 0x02ff_f000. */

struct __attribute__((__packed__)) hb_transfer_region {
	int16_t touch_x;
	int16_t touch_y;
	int16_t touch_x_px;
	int16_t touch_y_px;
	int16_t touch_z1;
	int16_t touch_z2;
	uint16_t extkeyin;
	uint16_t _pad;
	// +0x10
	time_t unix_time;
	struct hb_bootstub* bootcode;
	// +0x1c
};
static_assert(sizeof(time_t) == sizeof(uint64_t));
static_assert(offsetof(struct hb_transfer_region, unix_time) == 0x10);
static_assert(sizeof(struct hb_transfer_region) == 0x1c);

#define ABI_HB_TRANSFER_REGION (*(struct hb_transfer_region*)0x02fff000)

#endif

