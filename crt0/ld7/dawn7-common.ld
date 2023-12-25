
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(ResetHandler)

/*__sp_abt (+ exn/irq vector stuff) is -0x100..ewram2_end_REAL, because we keep
 * 256 bytes for it reserved in the memory map, the below expression is OK */
__sp_irq = ORIGIN(ewram2) + LENGTH(ewram2);
__sp_svc = __sp_irq - 0x100;
__sp_usr = __sp_svc - 0x100;
__sp_und = 0x0380ff60;

/* stuff CMSIS-Core wants */
PROVIDE(__StackTop = __sp_usr);
PROVIDE(__StackLimit = ORIGIN(ewram2));


__heap0_start = ORIGIN(ewram1);
__heap0_end   = ORIGIN(ewram1) + LENGTH(ewram1);


PHDRS {
	main    PT_LOAD FLAGS(7);
	wram    PT_LOAD FLAGS(7);
	twl     PT_LOAD FLAGS(0x100007);
}

