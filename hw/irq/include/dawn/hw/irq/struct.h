
#ifndef DAWN_HW_IRQ_STRUCT_H_
#define DAWN_HW_IRQ_STRUCT_H_

#include <dawn/hw/iobase.h>

#include <dawn/hw/irq/regs.h>


struct irq_hw {
	uint64_t _pad;
	uint32_t ime;
	uint32_t ie;
	uint32_t iflg;
#ifdef ARM7
	uint32_t ie2;
	uint32_t if2;
#endif
};


#define REG_IRQ_HW (*(volatile struct irq_hw*)IO_IRQ_BASE)


enum irq_number {
	irq_no_vblank  = REG_IF_VBLANK_Lsb,
	irq_no_hblank  = REG_IF_HBLANK_Lsb,
	irq_no_vcount  = REG_IF_VCOUNT_Lsb,
	irq_no_tm0ovf  = REG_IF_TM0OVF_Lsb, // TODO
	irq_no_tm1ovf  = REG_IF_TM1OVF_Lsb,
	irq_no_tm2ovf  = REG_IF_TM2OVF_Lsb,
	irq_no_tm3ovf  = REG_IF_TM3OVF_Lsb,
#ifdef ARM7
	irq_no_rtc     = REG_IF_RTC_Lsb,
#endif
	irq_no_dma0    = REG_IF_DMA0_Lsb,
	irq_no_dma1    = REG_IF_DMA1_Lsb,
	irq_no_dma2    = REG_IF_DMA2_Lsb,
	irq_no_dma3    = REG_IF_DMA3_Lsb,
	irq_no_key     = REG_IF_KEY_Lsb,
	irq_no_agbslot = REG_IF_AGBSLOT_Lsb,
	irq_no_gcddet  = REG_IF_GCD_DET_Lsb,
	irq_no_gcd2det = REG_IF_GCD2_DET_Lsb,
	irq_no_ipcsync = REG_IF_IPC_SYNC_Lsb,
	irq_no_ipc_wrfifo_empty = REG_IF_IPC_WRFIFO_E_Lsb,
	irq_no_ipc_rdfifo_avail = REG_IF_IPC_RDFIFO_A_Lsb,
	irq_no_gcd_dreq= REG_IF_GCD_DREQ_Lsb,
	irq_no_gcd_irq = REG_IF_GCD_IRQ_Lsb,
#ifdef ARM9
	irq_no_gpu_gxfifo = REG_IF_GPU_GXFIFO_Lsb,
#endif
#ifdef ARM7
	irq_no_hinge_open = REG_IF_HINGEOPEN_Lsb,
	irq_no_spi     = REG_IF_SPI_Lsb,
	irq_no_ntrwl   = REG_IF_NTRWL_Lsb,
#endif
#ifdef ARM9
	irq_no_dsp     = REG_IF_DSP_Lsb,
	irq_no_camera  = REG_IF_CAMERA_Lsb,
#endif
	irq_no_gcd2_dreq=REG_IF_GCD2_DREQ_Lsb,
	irq_no_gcd2_irq= REG_IF_GCD2_IRQ_Lsb,
	irq_no_ndma0   = REG_IF_NDMA0_Lsb,
	irq_no_ndma1   = REG_IF_NDMA1_Lsb,
	irq_no_ndma2   = REG_IF_NDMA2_Lsb,
	irq_no_ndma3   = REG_IF_NDMA3_Lsb,

#ifdef ARM7
	irq_no_gpio180  = REG_IF2_GPIO180_Lsb+32,
	irq_no_gpio181  = REG_IF2_GPIO181_Lsb+32,
	irq_no_gpio182  = REG_IF2_GPIO182_Lsb+32,
	irq_no_gpio330  = REG_IF2_GPIO330_Lsb+32,
	irq_no_hpnsp    = REG_IF2_HPnSP_Lsb+32,
	irq_no_power    = REG_IF2_POWER_Lsb+32,
	irq_no_gpio333  = REG_IF2_GPIO333_Lsb+32,
	irq_no_sdmc_ctl = REG_IF2_SDMC_CTL_Lsb+32,
	irq_no_sdmc_data1=REG_IF2_SDMC_DATA1_Lsb+32,
	irq_no_sdio_ctl = REG_IF2_SDIO_CTL_Lsb+32,
	irq_no_sdio_data1=REG_IF2_SDIO_DATA1_Lsb+32,
	irq_no_aes      = REG_IF2_AES_Lsb+32,
	irq_no_i2c      = REG_IF2_I2C_Lsb+32,
	irq_no_micext   = REG_IF2_MICEXT_Lsb+32,
#endif
};

enum irq_flags {
	irq_flag_vblank  = 1<<REG_IF_VBLANK_Lsb,
	irq_flag_hblank  = 1<<REG_IF_HBLANK_Lsb,
	irq_flag_vcount  = 1<<REG_IF_VCOUNT_Lsb,
	irq_flag_tm0ovf  = 1<<REG_IF_TM0OVF_Lsb, // TODO
	irq_flag_tm1ovf  = 1<<REG_IF_TM1OVF_Lsb,
	irq_flag_tm2ovf  = 1<<REG_IF_TM2OVF_Lsb,
	irq_flag_tm3ovf  = 1<<REG_IF_TM3OVF_Lsb,
#ifdef ARM7
	irq_flag_rtc     = 1<<REG_IF_RTC_Lsb,
#endif
	irq_flag_dma0    = 1<<REG_IF_DMA0_Lsb,
	irq_flag_dma1    = 1<<REG_IF_DMA1_Lsb,
	irq_flag_dma2    = 1<<REG_IF_DMA2_Lsb,
	irq_flag_dma3    = 1<<REG_IF_DMA3_Lsb,
	irq_flag_key     = 1<<REG_IF_KEY_Lsb,
	irq_flag_agbslot = 1<<REG_IF_AGBSLOT_Lsb,
	irq_flag_gcddet  = 1<<REG_IF_GCD_DET_Lsb,
	irq_flag_gcd2det = 1<<REG_IF_GCD2_DET_Lsb,
	irq_flag_ipcsync = 1<<REG_IF_IPC_SYNC_Lsb,
	irq_flag_ipc_wrfifo_empty = 1<<REG_IF_IPC_WRFIFO_E_Lsb,
	irq_flag_ipc_rdfifo_avail = 1<<REG_IF_IPC_RDFIFO_A_Lsb,
	irq_flag_gcd_dreq= 1<<REG_IF_GCD_DREQ_Lsb,
	irq_flag_gcd_irq = 1<<REG_IF_GCD_IRQ_Lsb,
#ifdef ARM9
	irq_flag_gpu_gxfifo = 1<<REG_IF_GPU_GXFIFO_Lsb,
#endif
#ifdef ARM7
	irq_flag_hinge_open = 1<<REG_IF_HINGEOPEN_Lsb,
	irq_flag_spi     = 1<<REG_IF_SPI_Lsb,
	irq_flag_ntrwl   = 1<<REG_IF_NTRWL_Lsb,
#endif
#ifdef ARM9
	irq_flag_dsp     = 1<<REG_IF_DSP_Lsb,
	irq_flag_camera  = 1<<REG_IF_CAMERA_Lsb,
#endif
	irq_flag_gcd2_dreq=1<<REG_IF_GCD2_DREQ_Lsb,
	irq_flag_gcd2_irq= 1<<REG_IF_GCD2_IRQ_Lsb,
	irq_flag_ndma0   = 1<<REG_IF_NDMA0_Lsb,
	irq_flag_ndma1   = 1<<REG_IF_NDMA1_Lsb,
	irq_flag_ndma2   = 1<<REG_IF_NDMA2_Lsb,
	irq_flag_ndma3   =1u<<REG_IF_NDMA3_Lsb,

#ifdef ARM7
	irq_flag_gpio180  = 1uLL<<(REG_IF2_GPIO180_Lsb+32),
	irq_flag_gpio181  = 1uLL<<(REG_IF2_GPIO181_Lsb+32),
	irq_flag_gpio182  = 1uLL<<(REG_IF2_GPIO182_Lsb+32),
	irq_flag_gpio330  = 1uLL<<(REG_IF2_GPIO330_Lsb+32),
	irq_flag_hpnsp    = 1uLL<<(REG_IF2_HPnSP_Lsb+32),
	irq_flag_power    = 1uLL<<(REG_IF2_POWER_Lsb+32),
	irq_flag_gpio333  = 1uLL<<(REG_IF2_GPIO333_Lsb+32),
	irq_flag_sdmc_ctl = 1uLL<<(REG_IF2_SDMC_CTL_Lsb+32),
	irq_flag_sdmc_data1=1uLL<<(REG_IF2_SDMC_DATA1_Lsb+32),
	irq_flag_sdio_ctl = 1uLL<<(REG_IF2_SDIO_CTL_Lsb+32),
	irq_flag_sdio_data1=1uLL<<(REG_IF2_SDIO_DATA1_Lsb+32),
	irq_flag_aes      = 1uLL<<(REG_IF2_AES_Lsb+32),
	irq_flag_i2c      = 1uLL<<(REG_IF2_I2C_Lsb+32),
	irq_flag_micext   = 1uLL<<(REG_IF2_MICEXT_Lsb+32),
#endif
};

#endif

