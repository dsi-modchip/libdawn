
MEMORY {
	/*
	 * The first ARM7 memory region is main RAM. or PSRAM/SDRAM. or FCRAM. or
	 * however you want to call it, really. It's large, and is divided up like
	 * this:
	 * * 0x0200_0000..0x0200_0c00: AutoLoad info block, part of the ABI. don't touch
	 * * 0x0200_0c00..0x0238_0000: ARM9 RAM for whatever it wishes to use it for.
	 *          This divide here is rather arbitrary, and you can make your own
	 *          linker scripts if you wish if you want to give one core more
	 *          memory than the other.
	 * * 0x0238_0000..0x023f_c000: ARM7 RAM for whatever it wishes to use it for.
	 * * 0x023f_c000..0x0240_0000: ABI bullshit with the ROM header and stuff
	 * * 0x0240_0000..0x0270_0000: extra ARM9 RAM for TWL mode
	 *          Again, arbitrary divide here
	 * * 0x0270_0000..0x027f_c000: extra ARM7 RAM for TWL mode
	 * * 0x027f_c000..0x0280_0000: ABI bullshit 'mirror' due to how the NTR BIOS works
	 * * 0x0280_0000..0x02e0_0000: extra ARM9 RAM for TWL mode
	 *          Again, arbitrary divide here
	 * * 0x02e0_0000..0x02ff_c000: extra ARM7 RAM for TWL mode
	 * * 0x02ff_c000..0x0300_0000: ABI bullshit 'mirror' due to how the TWL Sysmenu works
	 */
	psram_ntr : ORIGIN = 0x02380000, LENGTH = 0x00080000
	psram_twl1: ORIGIN = 0x02700000, LENGTH = 0x00100000 - 0x4000
	psram_twl2: ORIGIN = 0x02e00000, LENGTH = 0x00300000 - 0x4000
	psram_twl3: ORIGIN = 0x0dc00000, LENGTH = 0x00400000

	/*
	 * Alright, next up, SoC-internal SRAM aka WRAM. I'm going to ignore NWRAM
	 * here because a) it has ridiculous mapping rules, b) if you're using it
	 * chances are you're using it as temporary buffers to avoid bus contention
	 * or for the DSP or something weird.
	 *
	 * Anyway. First there's "EWRAM" or "shared WRAM" or whatever. By default
	 * in libtwl it's all allocated to the ARM7 because the ARM9 has the TCMs.
	 * The first half will be left unallocated (for you to use as a small heap
	 * or maybe to leave the possibility open to share it with the ARM9, set
	 * WRAMCNT to either 2 or 3). The second half is used as the stack. "IWRAM"
	 * or "ARM7-WRAM" will be used for code and data and all that jazz.
	 */
	ewram1: ORIGIN = 0x037f8000, LENGTH = 0x04000
	ewram2: ORIGIN = 0x037fc000, LENGTH = 0x02000 /* actually, cheat a little - use only 8k of stack instead of 16k, rest will also be code and stuff */
	iwram : ORIGIN = 0x03800000 - 0x2000, LENGTH = 0x2000 + 0x10000 - 0x100 /* leave out some data for exception vectors and stuff */
}

