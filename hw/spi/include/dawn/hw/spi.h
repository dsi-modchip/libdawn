
#ifndef DAWN_HW_SPI_H_
#define DAWN_HW_SPI_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/spi/struct.h>

void spi_transfer_blocking(volatile struct spi_hw* hw, int chip,
		bool cshold, size_t nbytes, const uint8_t* txbuf, uint8_t* rxbuf);

#endif

