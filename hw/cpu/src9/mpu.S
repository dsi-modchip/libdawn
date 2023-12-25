@ vim: set ft=armv5:

#include <dawn/hw/asminc.h>

	.arch armv5te
	.cpu arm946e-s

	.arm


	@ LOOKUP BITS: DDDIII -> PPPUUU
	@                        XWRXWR
	.section .dtcm.rodata.MPU_BIT_TO_FLAG_LUT, "a", %progbits
	.type MPU_BIT_TO_FLAG_LUT, %object
MPU_BIT_TO_FLAG_LUT:
	.byte 0x00, 0x20, 0x24, 0x24, 0x00, 0x20, 0x24, 0x00
	.byte 0x18, 0x38, 0x3c, 0x3c, 0x00, 0x38, 0x3c, 0x00
	.byte 0x19, 0x39, 0x3d, 0x3d, 0x00, 0x39, 0x3d, 0x00
	.byte 0x1b, 0x3b, 0x3f, 0x3f, 0x00, 0x3b, 0x3f, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0x28, 0x2c, 0x2c, 0x00, 0x28, 0x2c, 0x00
	.byte 0x09, 0x29, 0x2d, 0x2d, 0x00, 0x29, 0x2d, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.size MPU_BIT_TO_FLAG_LUT, . - MPU_BIT_TO_FLAG_LUT


	@ LOOKUP BITS: PPPUUU -> DDDIII
	@              XWRXWR
	.section .dtcm.rodata.MPU_FLAG_TO_BIT_LUT, "a", %progbits
	.type MPU_FLAG_TO_BIT_LUT, %object
MPU_FLAG_TO_BIT_LUT:
	.byte 0x00, 0x30, 0x18, 0x18, 0x06, 0x36, 0x1e, 0x1e
	.byte 0x28, 0x30, 0x18, 0x18, 0x2e, 0x36, 0x1e, 0x1e
	.byte 0x08, 0x10, 0x18, 0x18, 0x0e, 0x16, 0x1e, 0x1e
	.byte 0x08, 0x10, 0x18, 0x18, 0x0e, 0x16, 0x1e, 0x1e
	.byte 0x05, 0x35, 0x1d, 0x1d, 0x06, 0x36, 0x1e, 0x1e
	.byte 0x2d, 0x35, 0x1d, 0x1d, 0x2e, 0x36, 0x1e, 0x1e
	.byte 0x0d, 0x15, 0x1d, 0x1d, 0x0e, 0x16, 0x1e, 0x1e
	.byte 0x0d, 0x15, 0x1d, 0x1d, 0x0e, 0x16, 0x1e, 0x1e
	.size MPU_FLAG_TO_BIT_LUT, . - MPU_FLAG_TO_BIT_LUT


DAWN_BEGIN_FUNC mpu_region_info_get
	and r0, #7
	add pc, r0, lsl #3
	nop

.irp region, 0,1,2,3,4,5,6,7
	mrc p15, 0, r0, c6, c\region\(), 0
	bx  lr
.endr
DAWN_END_FUNC mpu_region_info_get

DAWN_BEGIN_FUNC mpu_region_set_region
	and r0, #7
	add pc, r0, lsl #3
	nop

.irp region, 0,1,2,3,4,5,6,7
	mcr p15, 0, r1, c6, c\region\(), 0
	bx  lr
.endr
DAWN_END_FUNC mpu_region_set_region

DAWN_BEGIN_FUNC mpu_region_info_set
	and r0, #7
	lsl r0, #2  @ r0 *= 4
	add r2, r0, r0, lsl #1  @ r2 = r0*3 = channel*12
	add pc, r2
	nop

.irp region, 0,1,2,3,4,5,6,7
	mrc p15, 0, r0, c6, c\region\(), 0
	mcr p15, 0, r1, c6, c\region\(), 0
	bx  lr
.endr
DAWN_END_FUNC mpu_region_info_set

DAWN_BEGIN_FUNC mpu_region_info_set_masked
	and r1, r2
	and r0, #7
	lsl r0, #2  @ r0 *= 4
	add r3, r0, r0, lsl #2  @ r3 = r0*5 = channel*20
	add pc, r3  @ pc += channel*20
	nop

.irp region, 0,1,2,3,4,5,6,7
	mrc p15, 0, r0, c6, c\region\(), 0
	bic r2, r0, r2
	orr r2, r1
	mcr p15, 0, r2, c6, c\region\(), 0
	bx  lr
.endr
DAWN_END_FUNC mpu_region_info_set_masked


DAWN_BEGIN_FUNC mpu_region_get_flags
	push {r4,lr}
	mov r3, r0
	mov r4, #1

	@ r0, r1: tmp
	@ r2: result acc
	@ r3: region no
	@ r4: imm 1

	@ enable bit
	bl  mpu_region_info_get
	and r2, r0, #1

	@ icache bit
	mrc p15, 0, r1, c2, c0, 1
	and r1, r4, r1, lsr r3
	orr r2, r1, lsl #1

	@ dcache bit
	mrc p15, 0, r1, c2, c0, 0
	and r1, r4, r1, lsr r3
	orr r2, r1, lsl #2

	@ dc_wb
	mrc p15, 0, r1, c3, c0, 0
	and r1, r4, r1, lsr r3
	orr r2, r1, lsl #3

	@ access bits
	lsl r3, #3  @ regionno *= 8
	mov r4, #7
	mrc p15, 0, r0, c5, c0, 2  @ data
	mrc p15, 0, r1, c5, c0, 3  @ insn
	and r0, r4, r0, lsr r3 @ extract out relevant nybble
	and r1, r4, r1, lsr r3 @ same but for insn
	ldr r4, =MPU_BIT_TO_FLAG_LUT
	orr r1, r0, lsl #3     @ combine
	ldrb r0, [r4, r1]     @ lookup in LUT

	orr r0, r2, r0, lsl #8 @ combine into final value

	pop {r4}
	pop {r3}
	bx   r3
DAWN_END_FUNC mpu_region_get_flags


@void mpu_region_set_props(int region uintptr_t base, enum mpu_region_size size,
@		enum mpu_flags flags);
DAWN_BEGIN_FUNC mpu_region_set_props
	push {r4,r5,lr}

	@ temp disable MPU if enabled
	mrc p15, 0, r5, c1, c0, 0
	bic r4, r5, #1
	mcr p15, 0, r4, c1, c0, 0

	@ set base & size & enable first
	and r4, r3, #1     @ extract enable bit
	orr r1, r4         @ add enable bit to base
	orr r1, r2, lsl #1 @ add size to base
	bl  mpu_region_set_region  @ set region stuff
	@ can now reuse r1, r2

	mov r4, #1

	@ r0: region
	@ r1: tmp (ic/dc/wb reg)
	@ r2: tmp
	@ r3: flags
	@ r4: imm 1
	@ r5: CP15 ctlreg backup

	@ set icache bit
	mrc p15, 0, r1, c2, c0, 1
	bic r1, r1, r4, lsl r0 @ keep info of other regions
	and r2, r4, r3, lsr #1 @ extract bit from flags
	orr r1, r1, r2         @ combine
	mcr p15, 0, r1, c2, c0, 1

	@ set dcache bit
	mrc p15, 0, r1, c2, c0, 0
	bic r1, r1, r4, lsl r0 @ keep info of other regions
	and r2, r4, r3, lsr #2 @ extract bit from flags
	orr r1, r1, r2         @ combine
	mcr p15, 0, r1, c2, c0, 0

	@ set writebuf bit
	mrc p15, 0, r1, c3, c0, 0
	bic r1, r1, r4, lsl r0 @ keep info of other regions
	and r2, r4, r3, lsr #3 @ extract bit from flags
	orr r1, r1, r2         @ combine
	mcr p15, 0, r1, c3, c0, 0

	@ r0: region
	@ r1: tmp (eaperm reg)
	@ r2: accbits
	@ r3: tmp
	@ r4: tmp
	@ r5: CP15 ctlreg backup

	@ iaperm, daperm
	mov  r4, #63
	ldr  r2, =MPU_FLAG_TO_BIT_LUT
	and  r3, r4, r3, lsr #8  @ extract accflags from flags
	ldrb r2, [r2, r3] @ LUT lookup

	mov r4, #7
	lsl r0, #2  @ regionno *= 4

	@ insn
	and r3, r2, #7
	mrc p15, 0, r1, c5, c0, 3
	bic r1, r4, lsl r0  @ clear bits that will be written
	orr r1, r3, lsl r0  @ write new bits
	mcr p15, 0, r1, c5, c0, 3

	@ data
	lsr r3, r2, #3
	mrc p15, 0, r1, c5, c0, 2
	bic r1, r4, lsl r0  @ clear bits that will be written
	orr r1, r3, lsl r0  @ write new bits
	mcr p15, 0, r1, c5, c0, 2

	@ reenable MPU again if it was disabled
	mcr p15, 0, r5, c1, c0, 0

	pop {r4,r5}
	pop {r3}
	bx   r3
DAWN_END_FUNC mpu_region_set_props



DAWN_BEGIN_FUNC mpu_dcache_bits_get
	mrc p15, 0, r0, c2, c0, 0
	bx  lr
DAWN_END_FUNC mpu_dcache_bits_get

DAWN_BEGIN_FUNC mpu_dcache_bits_set
	mrc p15, 0, r1, c2, c0, 0
	mcr p15, 0, r0, c2, c0, 0
	mov r0, r1
	bx  lr
DAWN_END_FUNC mpu_dcache_bits_set

DAWN_BEGIN_FUNC mpu_dcache_bits_set_masked
	and r0, r1
	mrc p15, 0, r2, c2, c0, 0
	bic r1, r2, r1
	orr r1, r0
	mov r0, r2
	mcr p15, 0, r1, c2, c0, 0
	bx  lr
DAWN_END_FUNC mpu_dcache_bits_set_masked


DAWN_BEGIN_FUNC mpu_icache_bits_get
	mrc p15, 0, r0, c2, c0, 1
	bx  lr
DAWN_END_FUNC mpu_icache_bits_get

DAWN_BEGIN_FUNC mpu_icache_bits_set
	mrc p15, 0, r1, c2, c0, 1
	mcr p15, 0, r0, c2, c0, 1
	mov r0, r1
	bx  lr
DAWN_END_FUNC mpu_icache_bits_set

DAWN_BEGIN_FUNC mpu_icache_bits_set_masked
	and r0, r1
	mrc p15, 0, r2, c2, c0, 1
	bic r1, r2, r1
	orr r1, r0
	mov r0, r2
	mcr p15, 0, r1, c2, c0, 1
	bx  lr
DAWN_END_FUNC mpu_icache_bits_set_masked


DAWN_BEGIN_FUNC mpu_wrbuf_bits_get
	mrc p15, 0, r0, c3, c0, 0
	bx  lr
DAWN_END_FUNC mpu_wrbuf_bits_get

DAWN_BEGIN_FUNC mpu_wrbuf_bits_set
	mrc p15, 0, r1, c3, c0, 0
	mcr p15, 0, r0, c3, c0, 0
	mov r0, r1
	bx  lr
DAWN_END_FUNC mpu_wrbuf_bits_set

DAWN_BEGIN_FUNC mpu_wrbuf_bits_set_masked
	and r0, r1
	mrc p15, 0, r2, c3, c0, 0
	bic r1, r2, r1
	orr r1, r0
	mov r0, r2
	mcr p15, 0, r1, c3, c0, 0
	bx  lr
DAWN_END_FUNC mpu_wrbuf_bits_set_masked


DAWN_BEGIN_FUNC mpu_accperm_i_get
	mrc p15, 0, r0, c5, c0, 3
	bx  lr
DAWN_END_FUNC mpu_accperm_i_get

DAWN_BEGIN_FUNC mpu_accperm_i_set
	mrc p15, 0, r1, c5, c0, 3
	mcr p15, 0, r0, c5, c0, 3
	mov r0, r1
	bx  lr
DAWN_END_FUNC mpu_accperm_i_set

DAWN_BEGIN_FUNC mpu_accperm_i_set_masked
	and r0, r1
	mrc p15, 0, r2, c5, c0, 3
	bic r1, r2, r1
	orr r1, r0
	mov r0, r2
	mcr p15, 0, r1, c5, c0, 3
	bx  lr
DAWN_END_FUNC mpu_accperm_i_set_masked


DAWN_BEGIN_FUNC mpu_accperm_d_get
	mrc p15, 0, r0, c5, c0, 2
	bx  lr
DAWN_END_FUNC mpu_accperm_d_get

DAWN_BEGIN_FUNC mpu_accperm_d_set
	mrc p15, 0, r1, c5, c0, 2
	mcr p15, 0, r0, c5, c0, 2
	mov r0, r1
	bx  lr
DAWN_END_FUNC mpu_accperm_d_set

DAWN_BEGIN_FUNC mpu_accperm_d_set_masked
	and r0, r1
	mrc p15, 0, r2, c5, c0, 2
	bic r1, r2, r1
	orr r1, r0
	mov r0, r2
	mcr p15, 0, r1, c5, c0, 2
	bx  lr
DAWN_END_FUNC mpu_accperm_d_set_masked


DAWN_BEGIN_FUNC mpu_initialize_full
	push {r4,r5}

	@ temp disable MPU if enabled
	mrc p15, 0, r5, c1, c0, 0
	bic r4, r5, #1
	mcr p15, 0, r4, c1, c0, 0

	@ set iap
	mcr p15, 0, r1, c5, c0, 3
	@ set dap
	mcr p15, 0, r2, c5, c0, 2

	@ now have r1,r2,r4 free

	mov r2, #0xff
	@ set icache
	and r1, r2, r0, lsr #0
	mcr p15, 0, r1, c2, c0, 1
	@ set dcache
	and r1, r2, r0, lsr #8
	mcr p15, 0, r1, c2, c0, 0
	@ set wrbuf
	and r1, r2, r0, lsr #16
	mcr p15, 0, r1, c3, c0, 0

	@ now have r0-r2,r4 free

	@ set region info of all 8 regions
.irp region, 0,1,2,3,4,5,6,7
	ldr r0, [r3], #4
	mcr p15, 0, r0, c6, c\region\(), 0
.endr

	@ reenable MPU again if it was disabled
	mcr p15, 0, r5, c1, c0, 0

	pop {r4,r5}
	bx   lr
DAWN_END_FUNC mpu_initialize_full

