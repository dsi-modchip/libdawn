
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(ResetHandler)

PROVIDE_HIDDEN(__itcm_size = 0x02000000); /* map ITCM along the entire 0..0x01ff_ffff region */
PROVIDE_HIDDEN(__dtcm_base = ORIGIN(dtcm_stack));
PROVIDE_HIDDEN(__dtcm_size = 0x4000);

/* must happen thru preprocessor stuff :/ */
/*PROVIDE_HIDDEN(__sp_abt_off = LENGTH(dtcm_stack));*/

__sp_irq = ORIGIN(dtcm_stack) + LENGTH(dtcm_stack);
__sp_und = __sp_irq - 0x080;
__sp_svc = __sp_und - 0x0c0;
__sp_usr = __sp_svc - 0x0c0;

/* stuff CMSIS-Core wants */
PROVIDE(__StackTop = __sp_usr);
PROVIDE(__StackLimit = ORIGIN(dtcm_stack));


PROVIDE_HIDDEN(__heap0_start = 0);
PROVIDE_HIDDEN(__heap0_end   = 0);


PHDRS {
	main    PT_LOAD FLAGS(7);
	dtcm    PT_LOAD FLAGS(7);
	itcm    PT_LOAD FLAGS(7);
	vectors PT_LOAD FLAGS(7);
	twl     PT_LOAD FLAGS(0x100007);
}

