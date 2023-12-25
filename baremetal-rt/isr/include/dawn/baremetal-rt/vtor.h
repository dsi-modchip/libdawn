
#ifndef DAWN_BAREMETALRT_VTOR_H_
#define DAWN_BAREMETALRT_VTOR_H_

struct libdawn_error_info {
	uint32_t r[16];
	uint32_t cpsr;
#ifdef ARM9
	uint32_t cp15_ctrl;
#endif
};

#ifdef ARM9
enum libdawn_error_mode {
	libdawn_error_und   = 0,
	libdawn_error_pabrt = 1,
	libdawn_error_dabrt = 2,
	libdawn_error_bios  = 3 /* went thru bios handler, reason unknown */
};


extern void __libdawn_handle_error(const struct libdawn_error_info* inf, enum libdawn_error_mode errmode);

void VTOR_SWI(void);
void VTOR_IRQ(void);
void VTOR_UND(void);
void VTOR_DABRT(void);
void VTOR_PABRT(void);

void VTOR_BIOS_DEBUG(void);
#elif defined(ARM7)
void VTOR_BIOS_DEBUG(void);

extern void __libdawn_handle_error(const struct libdawn_error_info* inf);
#endif

#endif

