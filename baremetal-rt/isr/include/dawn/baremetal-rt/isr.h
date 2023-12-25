
#ifndef DAWN_BAREMETALRT_ISR_H_
#define DAWN_BAREMETALRT_ISR_H_

#include <dawn/hw/irq.h>

void isr_handler(void);

isr_fn_t irq_get_handler(enum irq_number irqno);
isr_fn_t irq_set_handler(enum irq_number irqno, isr_fn_t fn);

/** code the interrupt handler will return to. if NULL, return immediately to
 * the interrupted code */
isr_fn_t isr_get_scheduler(void);
isr_fn_t isr_set_scheduler(isr_fn_t fn);

#define IRQ_HANDLER_DEF(x) void x(void)

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

#endif

