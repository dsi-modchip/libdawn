
MEMORY {
	/*
	 * We start at ITCM (32 KiB) at the fine address 0. It contains the
	 * exception vectors, and some code:
	 */
	vectors : ORIGIN = 0x00, LENGTH = 0x20
	itcm    : ORIGIN = 0x20, LENGTH = 0x8000 - 0x20
	/*
	 * Next up is main RAM/PSRAM/FCRAM/.... We already laid out the memory map
	 * in the ARM7 memory map file, but I'll repeat it here:
	 *
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
	psram_ntr : ORIGIN = 0x02000c00, LENGTH = 0x00380000 - 0x0c00
	psram_twl1: ORIGIN = 0x02400000, LENGTH = 0x00300000
	psram_twl2: ORIGIN = 0x02800000, LENGTH = 0x00600000
	psram_twl3: ORIGIN = 0x0d000000, LENGTH = 0x00c00000

	/*
	 * The final region is DTCM (16k) at 0x0b00_0000. Unorthodox choice, I
	 * know, but it lets us a) put the stack at the *start* of DTCM, and b)
	 * using the MPU, automatically detect stack overflows (which then go to
	 * the debug handler). Neat, isn't it? (Stack is 8k, just like on ARM7)
	 */
	dtcm_stack: ORIGIN = 0x0b000000, LENGTH = 0x2000 - 0x100 /* exception handling stack */
	dtcm      : ORIGIN = 0x0b002000, LENGTH = 0x2000 - 0x8 /* IF check bits & IRQ handler vector are here */
}

