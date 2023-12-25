
#ifndef DAWN_HW_ROM_COMMON_H_
#define DAWN_HW_ROM_COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/arm.h>


struct swi_Div_Result {
	int32_t div;
	int32_t rem;
	uint32_t absdiv;
};

struct swi_BitUnPack_Info {
	uint16_t srclen; /**< in bytes */
	uint8_t srcwidth; /**< source bit width (1/2/4/8) */
	uint8_t dstwidth; /**< destination bit width (1/2/4/8/16/32) */
	uint32_t offset_zeroflag;
};

enum swi_Compr_DataSize {
	swi_Compr_DataSize_Reserved  = 0,
	swi_Compr_DataSize_Diff8bit  = 1,
	swi_Compr_DataSize_Diff16bit = 2,
	swi_Compr_DataSize_Huff4bit  = 4,
	swi_Compr_DataSize_Huff8bit  = 8,
};
enum swi_Compr_Type {
	swi_Compr_Type_LZ77 = 1<<4,
	swi_Compr_Type_Huffman = 2<<4,
	swi_Compr_Type_RLE = 3<<4,
	swi_Compr_Type_DiffFilter = 8<<4,
};
struct swi_Compr_Header {
	uint8_t data_size_type;
	uint24_t decompr_size;
};
static_assert(sizeof(struct swi_Compr_Header) == sizeof(uint32_t));

struct swi_FileCallback {
	struct swi_Compr_Header (*open)(const void* src, void* dst, void* ud);
	void (*close)(const void* src);
	uint8_t (*read8)(const void* src);
	uint16_t (*read16)(const void* src);
	uint32_t (*read32)(const void* src);
};


static inline void swi_WaitByLoop(uint32_t n) { // 03
	ARM_SWI1(0x03, n);
}
#ifdef ARM7
void swi_IntrWait(bool always_wait, uint32_t flags, uint32_t flags2); // 04
void swi_VBlankIntrWait(); // 05
#else
void swi_IntrWait(bool always_wait, uint32_t flags); // 04
// always needs to use the fixed IntrWait version instead of the ROM one
static inline void swi_VBlankIntrWait() { swi_IntrWait(true, 1); }
#endif
static inline void swi_Halt() { // 06
#ifdef ARM9
	// destroys R0 on TWL9 (but easier to always ensure it's ok rather than
	// check the ROM version)
	ARM_SWI1(0x06, DONT_CARE(uint32_t));
#else
	ARM_SWI0(0x06);
#endif
}
static inline struct swi_Div_Result swi_Div(int32_t numer, int32_t denom) { // 09
	// copypaste from ARM_SWI3 a bit to catch the full return value
	register int32_t a0 __asm__("r0") = numer;
	register int32_t a1 __asm__("r1") = denom;
	register int32_t a2 __asm__("r2");
	__asm__ volatile(
		"swi %[num] << ((999f - . == 4) * -16); 999:\n"
		:"+r"(a0), "+r"(a1), "=r"(a2)
		:[num]"I"(0x09)
		:"memory"
	);
	return (struct swi_Div_Result){ .div = a0, .rem = a1, .absdiv = a2 };
}
/**
 * @param len if bit 26 of this parameter is set, use 32-bit transfers, else
 *            use 16-bit transfers. if bit 24 of this parameter is set, do a
 *            memset instead (src=ptr to const fillvalue)
 */
static inline void swi_CpuSet(const void* src, void* dst, size_t len) { // 0b
	ARM_SWI3(0x0b, src, dst, len);
}
/**
 * @param len if bit 24 of this parameter is set, do a memset instead (src=ptr to const fillvalue)
 */
static inline void swi_CpuFastSet(const void* src, void* dst, size_t len) { // 0c
	ARM_SWI3(0x0c, src, dst, len);
}
static inline uint32_t swi_Sqrt(uint32_t x) { // 0d
	return ARM_SWI1(0x0d, x);
}
static inline uint16_t swi_GetCRC16(uint16_t init, const uint16_t* src, size_t len) { // 0e
	return ARM_SWI4(0x0e, init, src, len, DONT_CARE(uint32_t)); // destroys R3
}
static inline void swi_BitUnPack(const void* src, uint32_t* dst,
		const struct swi_BitUnPack_Info* info) { // 10
	ARM_SWI3(0x10, src, dst, info);
}
static inline void swi_LZ77UnCompReadNormalWrite8bit(const struct swi_Compr_Header* src, void* dst) { // 11
	ARM_SWI2(0x11, src, dst);
}
static inline void swi_HuffUnCompReadByCallback(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs) { // 13
	ARM_SWI4(0x13, src, dst, ud, cbs);
}
static inline void swi_RLUnCompReadNormalWrite8bit(const struct swi_Compr_Header* src, void* dst) { // 14
	ARM_SWI2(0x14, src, dst);
}
static inline void swi_RLUnCompReadByCallbackWrite16bit(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs) { // 15
	ARM_SWI4(0x15, src, dst, ud, cbs);
}

void swi_LZ77UnCompReadByCallbackWrite16bit(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs); // 12/{02,19}
// NOTE: the SWI number is 0x12 on NTR, but 0x02 (or 0x19) on TWL, so we
//       need to get creative here

#endif

