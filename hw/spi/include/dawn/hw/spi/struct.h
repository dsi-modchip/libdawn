
#ifndef DAWN_HW_SPI_STRUCT_H_
#define DAWN_HW_SPI_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>

struct spi_hw {
	uint16_t cnt;
	uint8_t data;
};

#define REG_AUXSPI_HW (*(volatile struct spi_hw*)IO_GCD_BASE)
#define REG_AUXSPI2_HW (*(volatile struct spi_hw*)IO_GCD2_BASE)
#ifdef ARM7
#define REG_SPI_HW (*(volatile struct spi_hw*)IO_SPI_BASE)
#endif

#define AUX_SPICNT_CSHOLD_Msk 0x4040

#endif

