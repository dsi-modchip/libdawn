
INCLUDE "dawn7-memory.ld" /* memory map (or at least, the relevant parts) */

INCLUDE "dawn7-common.ld" /* common useful definitions */

SECTIONS {
	. = ORIGIN(psram_ntr);

	.text : {
		PROVIDE_HIDDEN(__LOAD_ORIGIN = ABSOLUTE(.));

		KEEP(*(.text.startup.ResetVector))
		*(.text.startup.*)
		KEEP(*(.text.*personality*)) /* these are for exception handlers */
		*(.text* .plt .stub .gnu.linkonce.t.* .glue_7t .glue_7 .vfp11_veneer .rodata* .gnu.linkonce.r.*)
		. = ALIGN(4);
	} >psram_ntr :main

	/* glue stuff for global constructors and destructors */
	.init : {
		KEEP(*(SORT_NONE(.init)))
		. = ALIGN(4);
	} >psram_ntr :main
	.fini : {
		KEEP(*(SORT_NONE(.fini)))
		. = ALIGN(4);
	} >psram_ntr :main
	.preinit_array : {
		PROVIDE_HIDDEN (__preinit_array_start = ABSOLUTE(.));
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = ABSOLUTE(.));
		. = ALIGN(4);
	} >psram_ntr :main
	.init_array : {
		PROVIDE_HIDDEN (__init_array_start = ABSOLUTE(.));
		KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
		KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
		PROVIDE_HIDDEN (__init_array_end = ABSOLUTE(.));
		. = ALIGN(4);
	} >psram_ntr :main
	.fini_array : {
		PROVIDE_HIDDEN (__fini_array_start = ABSOLUTE(.));
		KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
		KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
		PROVIDE_HIDDEN (__fini_array_end = ABSOLUTE(.));
		. = ALIGN(4);
	} >psram_ntr :main
	.ctors : {
		/* gcc uses crtbegin.o to find the start of the constructors, so we
		 * make sure it is first.  Because this is a wildcard, it doesn't
		 * matter if the user does not actually link against crtbegin.o; the
		 * linker won't look for a file to match a wildcard.  The wildcard also
		 * means that it doesn't matter which directory crtbegin.o is in.  */
		KEEP (*crtbegin.o(.ctors))
		KEEP (*crtbegin?.o(.ctors))
		/* We don't want to include the .ctor section from the crtend.o file
		 * until after the sorted ctors. The .ctor section from the crtend file
		 * contains the end of ctors marker and it must be last */
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
		. = ALIGN(4);
	} >psram_ntr :main
	.dtors : {
		KEEP (*crtbegin.o(.dtors))
		KEEP (*crtbegin?.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
		. = ALIGN(4);
	} >psram_ntr :main

	/* this stuff provides information for exception handling and printing of
	 * stack traces and stuff */
	.eh_frame_hdr : {
		*(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*)
		. = ALIGN(4);
	} >psram_ntr :main
	.eh_frame : {
		KEEP (*(.eh_frame)) *(.eh_frame.*)
		. = ALIGN(4);
	} >psram_ntr :main
	.gnu_extab : {
		*(.gnu_extab)
		. = ALIGN(4);
	} >psram_ntr :main
	.gcc_except_table : {
		*(.gcc_except_table .gcc_except_table.*)
		. = ALIGN(4);
	} >psram_ntr :main


	.data : {
		. = ALIGN(32);
		*(.data* .gnu.linkonce.d.* .got .igot)
		. = ALIGN(32);
		PROVIDE_HIDDEN(__tdata_start = ABSOLUTE(.));
		*(.tdata*) /* thread-local storage */
		. = ALIGN(32);
		__bss_start = ABSOLUTE(.);
		PROVIDE_HIDDEN(__tbss_start = ABSOLUTE(.)); /* this has to be contiguous with tdata */
		*(.tbss* .tcommon .gnu.linkonce.tb.*);
		. = ALIGN(4);
	} >psram_ntr :main

	.bss : {
		*(.bss* .gnu.linkonce.b.* COMMON)
		. = ALIGN(4);
		__bss_end = ABSOLUTE(.);
		. = ALIGN(32);
	} >psram_ntr :main

	PROVIDE(__heap2_start = .);
	PROVIDE(__heap2_end = ORIGIN(psram_ntr) + LENGTH(psram_ntr));


	/*** PSRAM-TWL ***********************************************************/

	. = ORIGIN(psram_twl1);

	.twl.text : {
		. = ALIGN(32);
		*(.twl.text* .twl.rodata*)
	} >psram_twl1 :twl
	.twl.data : {
		*(.twl.data*)
		. = ALIGN(4);
	} >psram_twl1 :twl
	.twl.bss : {
		. = ALIGN(32);
		__twl_bss_start = ABSOLUTE(.);
		*(.twl.bss*)
		. = ALIGN(4);
		__twl_bss_end = ABSOLUTE(.);
	} >psram_twl1 :twl

	PROVIDE(__heap3_start = .);
	PROVIDE(__heap3_end = ORIGIN(psram_twl1) + LENGTH(psram_twl1));

	. = ORIGIN(psram_twl2);
	PROVIDE(__heap4_start = .);
	PROVIDE(__heap4_end = ORIGIN(psram_twl2) + LENGTH(psram_twl2));


	/*** IWRAM ***************************************************************/

	. = ORIGIN(iwram);
	.wram.text : {
		__wram_text_start = ABSOLUTE(.);
		__wram_text_lma = ABSOLUTE(LOADADDR(.));
		*(.wram.text* .wram.rodata*)
		*(.wram.data*)
		. = ALIGN(4);
		__wram_text_end = ABSOLUTE(.);
	} >iwram AT>psram_ntr :wram
	.wram.bss : {
		. = ALIGN(32);
		__wram_bss_start = ABSOLUTE(.);
		*(.wram.bss*)
		. = ALIGN(4);
		__wram_bss_end = ABSOLUTE(.);
	} >iwram AT>psram_ntr :wram

	PROVIDE(__heap1_start = .);
	PROVIDE(__heap1_end   = ORIGIN(iwram) + LENGTH(iwram));


	/*** PSRAM-TWL (3: debug consoles) ***************************************/

	. = ORIGIN(psram_twl3);

	PROVIDE(__heap5_start = .);
	PROVIDE(__heap5_end = ORIGIN(psram_twl3) + LENGTH(psram_twl3));


	/*** misc stuff **********************************************************/

	PROVIDE(__bss_size = __bss_end - __bss_start);
	PROVIDE(__twl_bss_size = __twl_bss_end - __twl_bss_start);
	PROVIDE(__wram_text_size = __wram_text_end - __wram_text_start);
	PROVIDE(__wram_bss_size = __wram_bss_end - __wram_bss_start);

	/* debug info etc that should only be included in the ELF file but not the binary */
	INCLUDE "dawn-debug.ld"
}

