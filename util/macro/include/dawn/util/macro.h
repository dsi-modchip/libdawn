
#ifndef DAWN_UTIL_MACRO_H_
#define DAWN_UTIL_MACRO_H_

#include <stdint.h>
#include <assert.h>


typedef struct {
	uint32_t v: 24;
} __attribute__((packed)) uint24_t;

static_assert(sizeof(uint24_t) == 3);


#define COMPILER_BARRIER() do{__asm__ volatile("":::"memory");}while(0)

#define LTO_NO_INLINE(fn) __asm__ volatile(""::"X"(fn)); fn
#define LTO_NO_INLINE_CALL(fn, ...) ({LTO_NO_INLINE(fn)(__VA_ARGS__);})


#define __STR_HELPER(x) #x
#define STRINGIFY(x) __STR_HELPER(x)

#define   LIKELY(x) __builtin_expect (!!(x), 1)
#define UNLIKELY(x) __builtin_expect (!!(x), 0)

/*
 * This returns a constant expression while determining if an argument is
 * a constant expression, most importantly without evaluating the argument.
 * Glory to Martin Uecker <Martin.Uecker@med.uni-goettingen.de>
 */
#define __is_constexpr(x) \
        (sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))\

#define DONT_CARE(type) ({ \
		register type __a0; \
		__asm__ volatile("":"=r"(__a0)); \
		(__a0); \
	}) \


#ifndef MIN
#define MIN(x,y) ({__auto_type __a=(x);__auto_type __b=(y);__a<__b?__a:__b;})
#endif
#ifndef MAX
#define MAX(x,y) ({__auto_type __a=(x);__auto_type __b=(y);__a>__b?__a:__b;})
#endif
#ifndef CLAMP
#define CLAMP(x,y,z) MIN(MAX(x,y), z)
#endif
#ifndef ABS
#define ABS(x) ({__auto_type __y=(x);__y<0?-__y:__y;})
#endif

#ifndef offsetof
#define offsetof(type, member)  __builtin_offsetof (type, member)
#endif


#define HW_WRITE_MASKED(ptr, mask, flags) \
	({ \
		__auto_type __old = (ptr); \
		__auto_type __msk = (mask); \
		__auto_type __new = __old & ~(typeof(__msk))__msk; \
		(ptr) = __new | ((flags) & __msk); \
		(__old); \
	}) \


#ifdef __arm__
#define ARM_CODE __attribute__((__target__("arm")))
#define THUMB_CODE __attribute__((__target__("thumb")))
#endif

#define CONST_FN __attribute__((__const__))
#define PURE_FN __attribute__((__pure__))

#ifdef ARM9
#define ITCM_FUNC(x) __attribute__((__section__(".itcm.text."#x))) x
#define DTCM_VAR(x)  __attribute__((__section__(".dtcm.data."#x))) x
#define DTCM_CVAR(x) __attribute__((__section__(".dtcm.rodata."#x))) x
#define DTCM_BVAR(x) __attribute__((__section__(".dtcm.bss."#x))) x

#define FASTMEM_FUNC(x) ITCM_FUNC(x)
#define FASTMEM_VAR(x)  DTCM_VAR(x)
#define FASTMEM_CVAR(x) DTCM_CVAR(x)
#define FASTMEM_BVAR(x) DTCM_BVAR(x)
#endif

#ifdef ARM7
#define WRAM_FUNC(x) __attribute__((__section__(".wram.text."#x))) x
#define WRAM_VAR(x)  __attribute__((__section__(".wram.data."#x))) x
#define WRAM_CVAR(x) __attribute__((__section__(".wram.rodata."#x))) x
#define WRAM_BVAR(x) __attribute__((__section__(".wram.bss."#x))) x

#define FASTMEM_FUNC(x) WRAM_FUNC(x)
#define FASTMEM_VAR(x)  WRAM_VAR(x)
#define FASTMEM_CVAR(x) WRAM_CVAR(x)
#define FASTMEM_BVAR(x) WRAM_BVAR(x)
#endif


// trick stolen from https://github.com/LunarLambda/sdk-seven/blob/main/libseven/src/hw/bios.c
#define ARM_SWI0(swinum) do { \
		__asm__ volatile( \
			"swi %[num] << ((999f - . == 4) * -16); 999:\n" \
			: \
			:[num]"I"(swinum) \
			:"memory" \
		); \
	} while (0) \

#define ARM_SWI1(swinum, a0) ({ \
		register __auto_type __a0 __asm__("r0") = (a0); \
		__asm__ volatile( \
			"swi %[num] << ((999f - . == 4) * -16); 999:\n" \
			:"+r"(__a0) \
			:[num]"I"(swinum) \
			:"memory" \
		); \
		(__a0); \
	}) \

#define ARM_SWI2(swinum, a0, a1) ({ \
		register __auto_type __a0 __asm__("r0") = (a0); \
		register __auto_type __a1 __asm__("r1") = (a1); \
		__asm__ volatile( \
			"swi %[num] << ((999f - . == 4) * -16); 999:\n" \
			:"+r"(__a0), "+r"(__a1) \
			:[num]"I"(swinum) \
			:"memory" \
		); \
		(__a0); \
	}) \

#define ARM_SWI3(swinum, a0, a1, a2) ({ \
		register __auto_type __a0 __asm__("r0") = (a0); \
		register __auto_type __a1 __asm__("r1") = (a1); \
		register __auto_type __a2 __asm__("r2") = (a2); \
		__asm__ volatile( \
			"swi %[num] << ((999f - . == 4) * -16); 999:\n" \
			:"+r"(__a0), "+r"(__a1), "+r"(__a2) \
			:[num]"I"(swinum) \
			:"memory" \
		); \
		(__a0); \
	}) \

#define ARM_SWI4(swinum, a0, a1, a2, a3) ({ \
		register __auto_type __a0 __asm__("r0") = (a0); \
		register __auto_type __a1 __asm__("r1") = (a1); \
		register __auto_type __a2 __asm__("r2") = (a2); \
		register __auto_type __a3 __asm__("r3") = (a3); \
		__asm__ volatile( \
			"swi %[num] << ((999f - . == 4) * -16); 999:\n" \
			:"+r"(__a0), "+r"(__a1), "+r"(__a2), "+r"(__a3) \
			:[num]"I"(swinum) \
			:"memory" \
		); \
		(__a0); \
	}) \


#endif

