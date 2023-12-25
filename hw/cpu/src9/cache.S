@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>

	.arch armv5te
	.cpu arm946e-s

	.arm

DAWN_BEGIN_FUNC cache_dcache_flush, .itcm.text.cache_dcache_flush
	mov r3, #0

	mov  r1, #0
1:	mov  r0, #0x400
2:	orr  r2, r1, r0
	mcr  p15, 0, r3, c7, c10, 4 @ write buffer drain
	mcr  p15, 0, r2, c7, c10, 2
	subs r0, #0x20
	bne  2b

	adds r1, #0x40000000
	bne  1b

	bx lr
DAWN_END_FUNC cache_dcache_flush

DAWN_BEGIN_FUNC cache_dcache_flush_range, .itcm.text.cache_dcache_flush_range
	mov r3, #0

	add r1, r0
	bic r0, #0x1f
1:	mcr p15, 0, r3, c7, c10, 4 @ write buffer drain
	mcr p15, 0, r0, c7, c10, 1
	add r0, #0x20
	cmp r0, r1
	bne 1b

	bx lr
DAWN_END_FUNC cache_dcache_flush_range

DAWN_BEGIN_FUNC cache_dcache_flush_invalidate, .itcm.text.cache_dcache_flush_invalidate
	mov r3, #0

	mov  r1, #0
1:	mov  r0, #0x400
2:	orr  r2, r1, r0
	mcr  p15, 0, r3, c7, c10, 4 @ write buffer drain
	mcr  p15, 0, r2, c7, c14, 2
	subs r0, #0x20
	bne  2b

	adds r1, #0x40000000
	bne  1b

	bx lr
DAWN_END_FUNC cache_dcache_flush_invalidate

DAWN_BEGIN_FUNC cache_dcache_flush_invalidate_range, .itcm.text.cache_dcache_flush_invalidate_range
	mov r3, #0

	add r1, r0
	bic r0, #0x1f
1:	mcr p15, 0, r3, c7, c10, 4 @ write buffer drain
	mcr p15, 0, r0, c7, c14, 1
	add r0, #0x20
	cmp r0, r1
	bne 1b

	bx lr
DAWN_END_FUNC cache_dcache_flush_invalidate_range

DAWN_BEGIN_FUNC cache_dcache_invalidate, .itcm.text.cache_dcache_invalidate
	mov r0, #0
	mcr p15, 0, r0, c6, c10, 4 @ write buffer drain
	mcr p15, 0, r0, c7, c6, 0
	bx  lr
DAWN_END_FUNC cache_dcache_invalidate

DAWN_BEGIN_FUNC cache_dcache_invalidate_range, .itcm.text.cache_dcache_invalidate_range
	mov r3, #0

	add r1, r0
	bic r0, #0x1f
1:	mcr p15, 0, r3, c7, c10, 4 @ write buffer drain
	mcr p15, 0, r0, c7, c6, 1
	add r0, #0x20
	cmp r0, r1
	bne 1b

	bx lr
DAWN_END_FUNC cache_dcache_invalidate_range


DAWN_BEGIN_FUNC cache_icache_invalidate, .itcm.text.cache_icache_invalidate
	mov r0, #0
	mcr p15, 0, r0, c7, c5, 0
	bx  lr
DAWN_END_FUNC cache_icache_invalidate

DAWN_BEGIN_FUNC cache_icache_invalidate_range, .itcm.text.cache_icache_invalidate_range
	add r1, r0
	bic r0, #0x1f
1:	mcr p15, 0, r0, c7, c5, 1
	add r0, #0x20
	cmp r0, r1
	bne 1b

	bx lr
DAWN_END_FUNC cache_icache_invalidate_range

DAWN_BEGIN_FUNC cache_icache_prefetch_range, .itcm.text.cache_icache_prefetch_range
	add r1, r0
	bic r0, #0x1f
1:	mcr p15, 0, r0, c7, c13, 1
	add r0, #0x20
	cmp r0, r1
	bne 1b

	bx lr
DAWN_END_FUNC cache_icache_prefetch_range

DAWN_BEGIN_FUNC cache_icache_preload_range, .itcm.text.cache_icache_preload_range
	add r1, r0
	bic r0, #0x1f

1:	pld [r0]
	add  r0, #0x20
	cmp  r0, r1
	bne  1b

	bx lr
DAWN_END_FUNC cache_icache_preload_range


DAWN_BEGIN_FUNC cache_write_buffer_flush, .itcm.text.cache_write_buffer_flush
	mov r0, #0
	mcr p15, 0, r0, c7, c10, 4 @ write buffer drain
	bx  lr
DAWN_END_FUNC cache_write_buffer_flush

