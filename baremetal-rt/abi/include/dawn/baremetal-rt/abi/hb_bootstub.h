
#ifndef DAWN_BAREMETALRT_ABI_HB_BOOTSTUB_H_
#define DAWN_BAREMETALRT_ABI_HB_BOOTSTUB_H_

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

/** the 'bootstub' is a set of two functions a homebrew title can use to boot
 * back into its launcher. it is typically found at 0x02ff_????, with
 * <bootsize> bytes of code below it(?) implementing the two functions */


#define HB_BOOTSTUB_BOOTSIG ((uint64_t)0x627574734746f6f62uLL /* "bootstub" */)

typedef void (*hb_bootstub_fn)(void);

struct __attribute__((__packed__)) hb_bootstub {
	uint64_t bootsig;
	hb_bootstub_fn arm9reboot;
	hb_bootstub_fn arm7reboot;
	uint32_t bootsize;
};
static_assert(sizeof(struct hb_bootstub) == 0x14);

#endif

