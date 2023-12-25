@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>

	.arch armv5te
	.cpu arm946e-s

	.arm

DAWN_BEGIN_FUNC cp15_get_main_id
	mrc p15, 0, r0, c0, c0, 0
	bx  lr
DAWN_END_FUNC cp15_get_main_id

DAWN_BEGIN_FUNC cp15_get_cache_info
	mrc p15, 0, r0, c0, c0, 1
	bx  lr
DAWN_END_FUNC cp15_get_cache_info

DAWN_BEGIN_FUNC cp15_get_tcm_info
	mrc p15, 0, r0, c0, c0, 2
	bx  lr
DAWN_END_FUNC cp15_get_tcm_info


DAWN_BEGIN_FUNC cp15_control_get
	mrc p15, 0, r0, c1, c0, 0
	bx  lr
DAWN_END_FUNC cp15_control_get

DAWN_BEGIN_FUNC cp15_control_set, .itcm.text.cp15_control_set
	mrc p15, 0, r1, c1, c0, 0
	mcr p15, 0, r0, c1, c0, 0
	mov r0, r1
	bx  lr
DAWN_END_FUNC cp15_control_set

@ TODO: which memory should this be in? ITCM, DTCM, cache(FCRAM!) can all be disabled...
DAWN_BEGIN_FUNC cp15_control_set_masked, .itcm.text.cp15_control_set_masked
	and r0, r1
	mrc p15, 0, r2, c1, c0, 0
	bic r1, r2, r1
	orr r1, r0
	mov r0, r2
	mcr p15, 0, r1, c1, c0, 0
	bx  lr
DAWN_END_FUNC cp15_control_set_masked


DAWN_BEGIN_FUNC cp15_dtcm_get_info
	mrc p15, 0, r0, c9, c1, 0
	bx  lr
DAWN_END_FUNC cp15_dtcm_get_info

DAWN_BEGIN_FUNC cp15_itcm_get_info
	mrc p15, 0, r0, c9, c1, 1
	bx  lr
DAWN_END_FUNC cp15_itcm_get_info

DAWN_BEGIN_FUNC cp15_dtcm_set_info
	mrc p15, 0, r1, c9, c1, 0
	mcr p15, 0, r0, c9, c1, 0
	mov r0, r1
	bx  lr
DAWN_END_FUNC cp15_dtcm_set_info

DAWN_BEGIN_FUNC cp15_itcm_set_info
	mrc p15, 0, r1, c9, c1, 1
	mcr p15, 0, r0, c9, c1, 1
	mov r0, r1
	bx  lr
DAWN_END_FUNC cp15_itcm_set_info


DAWN_BEGIN_FUNC cp15_wfi, .itcm.text.cp15_wfi
	mov r0, #0
	mcr p15, 0, r0, c7, c0, 4
	bx  lr
DAWN_END_FUNC cp15_wfi

DAWN_BEGIN_FUNC cp15_get_etmprocid
	mrc p15, 0, r0, c13, c0, 1
	bx  lr
DAWN_END_FUNC cp15_get_etmprocid

DAWN_BEGIN_FUNC cp15_set_etmprocid
	mrc p15, 0, r1, c13, c0, 1
	mcr p15, 0, r0, c13, c0, 1
	mov r0, r1
	bx  lr
DAWN_END_FUNC cp15_set_etmprocid

