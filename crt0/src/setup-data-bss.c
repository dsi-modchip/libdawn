
#include <dawn/options.h>
#include <dawn/util/macro.h>
#include <dawn/hw/model.h>


#define REGION_MACRO(name) extern char __##name##_start[], __##name##_end[]
#define REGION_MACROS(name) extern char __##name##_start[], __##name##_end[], __##name##_size[]
#define REGION_MACROSL(name) extern char __##name##_start[], __##name##_end[], __##name##_size[], __##name##_lma[]


#ifdef ARM9
REGION_MACROSL(itcm);
REGION_MACROSL(dtcm_data);
REGION_MACROS(dtcm_bss);
#elif defined(ARM7)
REGION_MACROSL(wram_text);
REGION_MACROS(wram_bss);
#endif
REGION_MACROS(bss);
REGION_MACROS(twl_bss);

REGION_MACRO(heap1);
REGION_MACRO(heap2);
REGION_MACRO(heap3);
REGION_MACRO(heap4);
REGION_MACRO(heap5);


void __crt0_setup_data_and_bss(enum dawn_hw_model_type model);

typedef void (*memcpy_rom_fn)(const void* src, void* dst, size_t size);
typedef void (*memset_rom_fn)(uint32_t    src, void* dst, size_t size);

ARM_CODE static void crt0_memcpy(bool twl, void* dst, const void* src, size_t size) {
	if (!dst || !src || !size) return;

	size = (size + 3) >> 2;

	if (twl) {
#ifdef ARM9
		memcpy_rom_fn mrf = (memcpy_rom_fn)0xffff0808;
#elif defined(ARM7)
		memcpy_rom_fn mrf = (memcpy_rom_fn)0x10e0;
#endif
		mrf(src, dst, size);
	} else {
		ARM_SWI3(0xc, src, dst, size | (0<<24));
	}
}

ARM_CODE static void crt0_memset(bool twl, void* dst, uint32_t value, size_t size) {
	if (!dst || !size) return;

	size = (size + 3) >> 2;

	if (twl) {
#ifdef ARM9
		memset_rom_fn mrf = (memset_rom_fn)0xffff07bc;
#elif defined(ARM7)
		memset_rom_fn mrf = (memset_rom_fn)0x1094;
#endif
		mrf(value, dst, size);
	} else {
		ARM_SWI3(0xc, value, dst, size | (1<<24));
	}
}

__attribute__((__section__(".text.startup.__crt0_setup_data_and_bss")))
ARM_CODE void __crt0_setup_data_and_bss(enum dawn_hw_model_type model) {
	bool twl = (model & dawn_hw_model_model_mask) == dawn_hw_model_twl;
	size_t dram_mb = dawn_hw_model_get_dram_mb(model);

#ifdef ARM9
	crt0_memcpy(twl, __itcm_start, __itcm_lma, (size_t)__itcm_size);
	crt0_memcpy(twl, __dtcm_data_start, __dtcm_data_lma, (size_t)__dtcm_data_size);
	crt0_memset(twl, __dtcm_bss_start, 0, (size_t)__dtcm_bss_size);
#endif
#ifdef ARM7
	crt0_memcpy(twl, __wram_text_start, __wram_text_lma, (size_t)__wram_text_size);
	crt0_memset(twl, __wram_bss_start, 0, (size_t)__wram_bss_size);
#endif

	/*
	 * __bss_start..__bss_end
	 * __twl_bss_start..__twl_bss_end
	 * __heap_start..__heap_end
	 *   heap1: DTCM(9)/IWRAM(7)
	 *   heap2: NTRPSRAM
	 *   heap3: DBGPSRAM
	 *   heap4: TWLPSRAM
	 *   heap5: TWLDBG
	 */

	crt0_memset(twl, __bss_start, 0, (size_t)__bss_size);
	if (dram_mb >= 16) {
		crt0_memset(twl, __twl_bss_start, 0, (size_t)__twl_bss_size);
	}

	if (LIBDAWN_CLEAR_HEAP_MEMORY) {
		crt0_memset(twl, __heap1_start, LIBDAWN_CLEAR_HEAP_MEMORY_VALUE, __heap1_end - __heap1_start);
		crt0_memset(twl, __heap2_start, LIBDAWN_CLEAR_HEAP_MEMORY_VALUE, __heap2_end - __heap2_start);

		if (dram_mb >= 8) {
			crt0_memset(twl, __heap3_start, LIBDAWN_CLEAR_HEAP_MEMORY_VALUE, __heap3_end - __heap3_start);
		}
		if (dram_mb >= 16) {
			crt0_memset(twl, __heap4_start, LIBDAWN_CLEAR_HEAP_MEMORY_VALUE, __heap4_end - __heap4_start);
		}
		if (dram_mb > 16) {
			crt0_memset(twl, __heap5_start, LIBDAWN_CLEAR_HEAP_MEMORY_VALUE, __heap5_end - __heap5_start);
		}
	}
}

