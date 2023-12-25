
#ifndef DAWN_HW_ROM_TWLCRYPT_H_
#define DAWN_HW_ROM_TWLCRYPT_H_

#include <dawn/hw/arm.h>


struct swi_RSA_HeapInfo {
	void* start;
	void* end;
	size_t size;
};
struct swi_RSA_PtrInfo {
	void* dst; /**< 0x7f or 0x80 bytes */
	void* src; /**< 0x80 bytes */
	void* pubkey; /**< 0x80 bytes */
};


typedef int (*swi_SHA1_Callback_fn)(struct swi_SHA1_Context* ctx, const void* src, size_t len);

struct swi_SHA1_Context {
	uint8_t digest[20];
	uint64_t total_len;
	uint8_t buffer[64];
	uint32_t fragment;
	swi_SHA1_Callback_fn callback; /**< NULL for default callback */
};


static inline void swi_RSA_Init_crypto_heap(struct swi_RSA_HeapInfo* heap, void* start, size_t size) { // 20
	ARM_SWI3(0x20, heap, start, size);
}
/** @brief same as public-key encryption
 * @param out_len length of the destination is written back here */
static inline bool swi_RSA_Verify(struct swi_RSA_HeapInfo* heap, struct swi_RSA_PtrInfo* ptrs, size_t* out_len) { // 21
	return ARM_SWI3(0x21, heap, ptrs, out_len);
}
static inline bool swi_RSA_Verify_Unpad(struct swi_RSA_HeapInfo* heap, void* dst, const void* src, const void* key) { // 22
	return ARM_SWI4(0x22, heap, dst, src, key);
}
static inline void swi_RSA_Verify_Unpad_OpenPGP_SHA1(struct swi_RSA_HeapInfo* heap, void* dst, const void* src, const void* key) { // 23
	return ARM_SWI4(0x23, heap, dst, src, key);
}

static inline void swi_SHA1_Init(struct swi_SHA1_Context* ctx) { // 24
	ARM_SWI1(0x24, ctx);
}
static inline void swi_SHA1_Update(struct swi_SHA1_Context* ctx, const void* src, size_t len) { // 25
	ARM_SWI3(0x25, ctx, src, len);
}
static inline void swi_SHA1_Finish(uint8_t dst[static 20], struct swi_SHA1_Context* ctx) { // 26
	ARM_SWI2(0x26, dst, ctx);
}
static inline int swi_SHA1_Init_update_fin(uint8_t dst[static 20], const void* src, size_t len) { // 27
	return ARM_SWI3(0x27, dst, src, len);
}
static inline bool swi_SHA1_Compare_20_bytes(const uint8_t a[static 20], const uint8_t b[static 20]) { // 28
	return ARM_SWI2(0x28, a, b);
}
static inline void swi_SHA1_Random(void* dst, size_t dstlen, const void* src, size_t srclen) { // 29
	return ARM_SWI4(0x29, dst, dstlen, src, srclen);
}

#endif

