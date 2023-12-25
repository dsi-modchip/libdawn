@ vim: set ft=armv4:

	.arch armv4t
	.arm

#include <dawn/hw/asminc.h>

DAWN_BEGIN_FUNC_FASTMEM power_haltcnt_wfi
	mov  r0, #0x80
	mov  r1, #0x04000000
	strb r0, [r1, #0x0301]
	nop
	nop
	bx lr
DAWN_END_FUNC power_haltcnt_wfi

