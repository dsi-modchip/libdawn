
#include <stddef.h>

#include <dawn/hw/arm.h>

#include <dawn/baremetal-rt/isr.h>

#ifdef ARM7
#define NUM_IRQ 47
#elif defined(ARM9)
#define NUM_IRQ 32
#endif

extern void __irq_handler_default(void);
extern void __isr_scheduler_default(void);

extern isr_fn_t __isr_sched;
isr_fn_t FASTMEM_VAR(__isr_sched) __attribute__((__used__)) = __isr_scheduler_default;

extern isr_fn_t __isr_table[NUM_IRQ];

isr_fn_t irq_get_handler(enum irq_number irqno) { return __isr_table[irqno]; }
isr_fn_t irq_set_handler(enum irq_number irqno, isr_fn_t fn) {
	if (fn == NULL) fn = __irq_handler_default;
	isr_fn_t old;
	CRITICAL_SECTION({
		old = __isr_table[irqno];
		__isr_table[irqno] = fn;
	});
	return old;
}

isr_fn_t isr_get_scheduler(void) { return __isr_sched; }
isr_fn_t isr_set_scheduler(isr_fn_t fn) {
	if (fn == NULL) fn = __isr_scheduler_default;
	isr_fn_t old;
	CRITICAL_SECTION({
		old = __isr_sched;
		__isr_sched = fn;
	});
	return old;
}

isr_fn_t FASTMEM_VAR(__isr_table)[NUM_IRQ] __attribute__((__used__)) = {
	[irq_no_vblank] = irq_handler_vblank,
	[irq_no_hblank] = irq_handler_hblank,
	[irq_no_vcount] = irq_handler_vcount,
	[irq_no_tm0ovf] = irq_handler_tm0ovf,
	[irq_no_tm1ovf] = irq_handler_tm1ovf,
	[irq_no_tm2ovf] = irq_handler_tm2ovf,
	[irq_no_tm3ovf] = irq_handler_tm3ovf,
#ifdef ARM7
	[irq_no_rtc] = irq_handler_rtc,
#endif
	[irq_no_dma0] = irq_handler_dma0,
	[irq_no_dma1] = irq_handler_dma1,
	[irq_no_dma2] = irq_handler_dma2,
	[irq_no_dma3] = irq_handler_dma3,
	[irq_no_key] = irq_handler_key,
	[irq_no_agbslot] = irq_handler_agbslot,
	[irq_no_gcddet] = irq_handler_gcddet,
	[irq_no_gcd2det] = irq_handler_gcd2det,
	[irq_no_ipcsync] = irq_handler_ipcsync,
	[irq_no_ipc_wrfifo_empty] = irq_handler_ipc_wrfifo_empty,
	[irq_no_ipc_rdfifo_avail] = irq_handler_ipc_rdfifo_avail,
	[irq_no_gcd_dreq] = irq_handler_gcd_dreq,
	[irq_no_gcd_irq] = irq_handler_gcd_irq,
#ifdef ARM9
	[irq_no_gpu_gxfifo] = irq_handler_gpu_gxfifo,
#endif
#ifdef ARM7
	[irq_no_hinge_open] = irq_handler_hinge_open,
	[irq_no_spi] = irq_handler_spi,
	[irq_no_ntrwl] = irq_handler_ntrwl,
#endif
#ifdef ARM9
	[irq_no_dsp] = irq_handler_dsp,
	[irq_no_camera] = irq_handler_camera,
#endif
	[irq_no_gcd2_dreq] = irq_handler_gcd2_dreq,
	[irq_no_gcd2_irq] = irq_handler_gcd2_irq,
	[irq_no_ndma0] = irq_handler_ndma0,
	[irq_no_ndma1] = irq_handler_ndma1,
	[irq_no_ndma2] = irq_handler_ndma2,
	[irq_no_ndma3] = irq_handler_ndma3,

#ifdef ARM7
	[irq_no_gpio180] = irq_handler_gpio180,
	[irq_no_gpio181] = irq_handler_gpio181,
	[irq_no_gpio182] = irq_handler_gpio182,
	[irq_no_gpio330] = irq_handler_gpio330,
	[irq_no_hpnsp] = irq_handler_hpnsp,
	[irq_no_power] = irq_handler_power,
	[irq_no_gpio333] = irq_handler_gpio333,
	[irq_no_sdmc_ctl] = irq_handler_sdmc_ctl,
	[irq_no_sdmc_data1] = irq_handler_sdmc_data1,
	[irq_no_sdio_ctl] = irq_handler_sdio_ctl,
	[irq_no_sdio_data1] = irq_handler_sdio_data1,
	[irq_no_aes] = irq_handler_aes,
	[irq_no_i2c] = irq_handler_i2c,
	[irq_no_micext] = irq_handler_micext,
#endif
};

__attribute__((__weak__)) void __irq_handler_default(void) { }

#define IRQ_HANDLER_DEF(x) void x(void) __attribute__((__weak__, __alias__("__irq_handler_default")))

IRQ_HANDLER_DEF(irq_handler_vblank);
IRQ_HANDLER_DEF(irq_handler_hblank);
IRQ_HANDLER_DEF(irq_handler_vcount);
IRQ_HANDLER_DEF(irq_handler_tm0ovf);
IRQ_HANDLER_DEF(irq_handler_tm1ovf);
IRQ_HANDLER_DEF(irq_handler_tm2ovf);
IRQ_HANDLER_DEF(irq_handler_tm3ovf);
#ifdef ARM7
IRQ_HANDLER_DEF(irq_handler_rtc);
#endif
IRQ_HANDLER_DEF(irq_handler_dma0);
IRQ_HANDLER_DEF(irq_handler_dma1);
IRQ_HANDLER_DEF(irq_handler_dma2);
IRQ_HANDLER_DEF(irq_handler_dma3);
IRQ_HANDLER_DEF(irq_handler_key);
IRQ_HANDLER_DEF(irq_handler_agbslot);
IRQ_HANDLER_DEF(irq_handler_gcddet);
IRQ_HANDLER_DEF(irq_handler_gcd2det);
IRQ_HANDLER_DEF(irq_handler_ipcsync);
IRQ_HANDLER_DEF(irq_handler_ipc_wrfifo_empty);
IRQ_HANDLER_DEF(irq_handler_ipc_rdfifo_avail);
IRQ_HANDLER_DEF(irq_handler_gcd_dreq);
IRQ_HANDLER_DEF(irq_handler_gcd_irq);
#ifdef ARM9
IRQ_HANDLER_DEF(irq_handler_gpu_gxfifo);
#endif
#ifdef ARM7
IRQ_HANDLER_DEF(irq_handler_hinge_open);
IRQ_HANDLER_DEF(irq_handler_spi);
IRQ_HANDLER_DEF(irq_handler_ntrwl);
#endif
#ifdef ARM9
IRQ_HANDLER_DEF(irq_handler_dsp);
IRQ_HANDLER_DEF(irq_handler_camera);
#endif
IRQ_HANDLER_DEF(irq_handler_gcd2_dreq);
IRQ_HANDLER_DEF(irq_handler_gcd2_irq);
IRQ_HANDLER_DEF(irq_handler_ndma0);
IRQ_HANDLER_DEF(irq_handler_ndma1);
IRQ_HANDLER_DEF(irq_handler_ndma2);
IRQ_HANDLER_DEF(irq_handler_ndma3);

#ifdef ARM7
IRQ_HANDLER_DEF(irq_handler_gpio180);
IRQ_HANDLER_DEF(irq_handler_gpio181);
IRQ_HANDLER_DEF(irq_handler_gpio182);
IRQ_HANDLER_DEF(irq_handler_gpio330);
IRQ_HANDLER_DEF(irq_handler_hpnsp);
IRQ_HANDLER_DEF(irq_handler_power);
IRQ_HANDLER_DEF(irq_handler_gpio333);
IRQ_HANDLER_DEF(irq_handler_sdmc_ctl);
IRQ_HANDLER_DEF(irq_handler_sdmc_data1);
IRQ_HANDLER_DEF(irq_handler_sdio_ctl);
IRQ_HANDLER_DEF(irq_handler_sdio_data1);
IRQ_HANDLER_DEF(irq_handler_aes);
IRQ_HANDLER_DEF(irq_handler_i2c);
IRQ_HANDLER_DEF(irq_handler_micext);
#endif

#undef IRQ_HANDLER_DEF

