
#ifndef DAWN_HW_CPU_CACHE_H_
#define DAWN_HW_CPU_CACHE_H_

#ifndef ARM9
#error "The cache is exclusive to the ARM9."
#endif

#include <dawn/hw/cpu/cp15.h>

static inline size_t cache_get_icache_size(void) {
	uint32_t r = cp15_get_cache_info();
	r = (r >>  0) & ((1u << 12) - 1);

	uint32_t //l = (r >> 0) & 3,
			 m = (r >> 2) & 1,
			 a = (r >> 3) & 7,
			 s = (r >> 6) & 7;

	if (a == 0 && m == 1) return 0;
	return (0x200u + (0x100u * m)) << s;
}
static inline int cache_get_icache_assoc(void) {
	uint32_t r = cp15_get_cache_info();
	r = (r >>  0) & ((1u << 12) - 1);

	uint32_t //l = (r >> 0) & 3,
			 m = (r >> 2) & 1,
			 a = (r >> 3) & 7/*,
			 s = (r >> 6) & 7*/;

	if (a == 0 && m == 1) return -1;
	return ((2u + m) << a) >> 1;
}
static inline size_t cache_get_icache_line_size(void) {
	uint32_t r = cp15_get_cache_info();
	r = (r >>  0) & ((1u << 12) - 1);

	uint32_t l = (r >> 0) & 3,
			 m = (r >> 2) & 1,
			 a = (r >> 3) & 7/*,
			 s = (r >> 6) & 7*/;

	if (a == 0 && m == 1) return 0;
	return 8u << l;
}


static inline size_t cache_get_dcache_size(void) {
	uint32_t r = cp15_get_cache_info();
	r = (r >> 12) & ((1u << 12) - 1);

	uint32_t //l = (r >> 0) & 3,
			 m = (r >> 2) & 1,
			 a = (r >> 3) & 7,
			 s = (r >> 6) & 7;

	if (a == 0 && m == 1) return 0;
	return (0x200u + (0x100u * m)) << s;
}
static inline int cache_get_dcache_assoc(void) {
	uint32_t r = cp15_get_cache_info();
	r = (r >> 12) & ((1u << 12) - 1);

	uint32_t //l = (r >> 0) & 3,
			 m = (r >> 2) & 1,
			 a = (r >> 3) & 7/*,
			 s = (r >> 6) & 7*/;

	if (a == 0 && m == 1) return -1;
	return ((2u + m) << a) >> 1;
}
static inline size_t cache_get_dcache_line_size(void) {
	uint32_t r = cp15_get_cache_info();
	r = (r >> 12) & ((1u << 12) - 1);

	uint32_t l = (r >> 0) & 3,
			 m = (r >> 2) & 1,
			 a = (r >> 3) & 7/*,
			 s = (r >> 6) & 7*/;

	if (a == 0 && m == 1) return 0;
	return 8u << l;
}


static inline bool cache_icache_is_enabled(void) {
	return (cp15_control_get() & cp15_ctl_icache_enable) != 0;
}
static inline bool cache_dcache_is_enabled(void) {
	return (cp15_control_get() & cp15_ctl_dcache_enable) != 0;
}
static inline bool cache_icache_enable(bool enable) {
	return cp15_control_set_masked((enable ? cp15_ctl_icache_enable : 0), cp15_ctl_icache_enable);
}
static inline bool cache_dcache_enable(bool enable) {
	return cp15_control_set_masked((enable ? cp15_ctl_dcache_enable : 0), cp15_ctl_dcache_enable);
}


void cache_dcache_flush(void);
void cache_dcache_flush_range(volatile void* addr, size_t size);
void cache_dcache_flush_invalidate(void);
void cache_dcache_flush_invalidate_range(volatile void* addr, size_t size);
void cache_dcache_invalidate(void);
void cache_dcache_invalidate_range(volatile void* addr, size_t size);

void cache_icache_invalidate(void);
void cache_icache_invalidate_range(volatile void* addr, size_t size);
void cache_icache_preload_range(volatile void* addr, size_t size);
void cache_icache_prefetch_range(volatile void* addr, size_t size);

void cache_write_buffer_flush(void);

// TODO: implement this? ??
///** segment: 0..3, data is 1024 bytes. NULL to disable lockdown */
//void cache_dcache_lockdown(int segment, const void* data);
///** segment: 0..3, data is 2048 bytes. NULL to disable lockdown */
//void cache_icache_lockdown(int segment, const void* data);

// TODO: debug access?

#endif

