
#include <dawn/hw/model.h>

#include <dawn/hw/rom/common.h>

typedef void (*lz77un_fn)(const struct swi_Compr_Header* src, void* dst,
		void* ud, const struct swi_FileCallback* cbs);

// we could also do this using self-modifying code, but eh, that's kinda
// annoying on the ARM9
static void lz77un_twl(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs) {
	ARM_SWI4(0x02, src, dst, ud, cbs);
}
static void lz77un_ntr(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs) {
	ARM_SWI4(0x12, src, dst, ud, cbs);
}

static lz77un_fn resolve_lz77un(void) {
	if (dawn_hw_model_is_twl_mode()) return lz77un_twl;
	else return lz77un_ntr;
}

void swi_LZ77UnCompReadByCallbackWrite16bit(const struct swi_Compr_Header* src,
		void* dst, void* ud, const struct swi_FileCallback* cbs)
	__attribute__((__ifunc__("resolve_lz77un")));

