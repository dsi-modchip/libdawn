
INCLUDE "dawn7-memory.ld" /* memory map (or at least, the relevant parts) */

INCLUDE "dawn7-common.ld" /* common useful definitions */

SECTIONS {
	.text : {
		PROVIDE_HIDDEN(__LOAD_ORIGIN = ABSOLUTE(.));

		KEEP(*(.text.startup.ResetVector))
		*(.text.startup.*)
		KEEP(*(.text.*personality*)) /* these are for exception handlers */
		*(.text* .twl.text* .wram.text* .plt .stub .gnu.linkonce.t.* .glue_7t .glue_7 .vfp11_veneer .rodata* .twl.rodata* .wram.rodata* .gnu.linkonce.r.*)
		. = ALIGN(4);
	} >iwram =0xff

	/* glue stuff for global constructors and destructors */
	.init : {
		KEEP(*(SORT_NONE(.init)))
		. = ALIGN(4);
	} >iwram =0xff
	.fini : {
		KEEP(*(SORT_NONE(.fini)))
		. = ALIGN(4);
	} >iwram =0xff
	.preinit_array : {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		. = ALIGN(4);
	} >iwram =0xff
	.init_array : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
		KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
		PROVIDE_HIDDEN (__init_array_end = .);
		. = ALIGN(4);
	} >iwram =0xff
	.fini_array : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
		KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
		PROVIDE_HIDDEN (__fini_array_end = .);
		. = ALIGN(4);
	} >iwram =0xff
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
	} >iwram =0xff
	.dtors : {
		KEEP (*crtbegin.o(.dtors))
		KEEP (*crtbegin?.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
		. = ALIGN(4);
	} >iwram =0xff

	/* this stuff provides information for exception handling and printing of
	 * stack traces and stuff */
	.eh_frame_hdr : {
		*(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*)
		. = ALIGN(4);
	} >iwram =0xff
	.eh_frame : ONLY_IF_RW {
		KEEP (*(.eh_frame)) *(.eh_frame.*)
		. = ALIGN(4);
	} >iwram =0xff
	.gnu_extab : ONLY_IF_RW {
		*(.gnu_extab)
		. = ALIGN(4);
	} >iwram =0xff
	.gcc_except_table : ONLY_IF_RW {
		*(.gcc_except_table .gcc_except_table.*)
		. = ALIGN(4);
	} >iwram =0xff


	.data : {
		. = ALIGN(32);
		__data_start = ABSOLUTE(.);
		*(.data* .twl.data* .wram.data* .gnu.linkonce.d.* .got .igot)
		PROVIDE_HIDDEN(__tdata_start = ABSOLUTE(.));
		*(.tdata*) /* thread-local storage */
		. = ALIGN(4);
		__data_end = ABSOLUTE(.);
		. = ALIGN(32);
		__bss_start = ABSOLUTE(.);
		PROVIDE_HIDDEN(__tbss_start = ABSOLUTE(.)); /* this has to be contiguous with tdata */
		*(.tbss* .tcommon .gnu.linkonce.tb.*);
		. = ALIGN(4);
	} >iwram =0xff

	.bss : {
		*(.bss* .twl.data* .wram.bss* .gnu.linkonce.b.* COMMON)
		. = ALIGN(4);
		__bss_end = ABSOLUTE(.);
	} >iwram =0xff

	PROVIDE(__heap1_start = .);
	PROVIDE(__heap1_end = ORIGIN(iwram) + LENGTH(iwram));


	/*** misc stuff **********************************************************/

	/* provide dummy values for symbols declared in the psram version */
	PROVIDE_HIDDEN(__twl_bss_start = 0);
	PROVIDE_HIDDEN(__twl_bss_end   = 0);

	PROVIDE_HIDDEN(__wram_text_start = 0);
	PROVIDE_HIDDEN(__wram_text_lma   = 0);
	PROVIDE_HIDDEN(__wram_text_end   = 0);
	PROVIDE_HIDDEN(__wram_bss_start  = 0);
	PROVIDE_HIDDEN(__wram_bss_end    = 0);

	PROVIDE_HIDDEN(__heap2_start = 0);
	PROVIDE_HIDDEN(__heap2_end   = 0);
	PROVIDE_HIDDEN(__heap3_start = 0);
	PROVIDE_HIDDEN(__heap3_end   = 0);
	PROVIDE_HIDDEN(__heap4_start = 0);
	PROVIDE_HIDDEN(__heap4_end   = 0);
	PROVIDE_HIDDEN(__heap5_start = 0);
	PROVIDE_HIDDEN(__heap5_end   = 0);

	PROVIDE(__bss_size = __bss_end - __bss_start);
	PROVIDE_HIDDEN(__twl_bss_size = __twl_bss_end - __twl_bss_start);
	PROVIDE_HIDDEN(__wram_text_size = __wram_text_end - __wram_text_start);
	PROVIDE_HIDDEN(__wram_bss_size = __wram_bss_end - __wram_bss_start);

	/* debug info etc that should only be included in the ELF file but not the binary */
	INCLUDE "dawn-debug.ld"
}

