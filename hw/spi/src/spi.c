
#include <dawn/hw/arm.h>

#include <dawn/hw/spi.h>
#include <dawn/hw/spi/regs.h>

void spi_transfer_blocking(volatile struct spi_hw* hw, int chip,
		bool cshold, size_t nbytes, const uint8_t* txbuf, uint8_t* rxbuf) {
	if (nbytes == 0) return;

	uint16_t cnt = hw->cnt & (REG_AUXSPICNT_IE_Msk | REG_AUXSPICNT_ENABLE_Msk);
	cnt |= REG_AUXSPICNT_ENABLE_Msk;

	// XXX: hack to always use SPIflash mode on AUXSPI bus, but use selected
	// chip on ARM7 SPI bus
	cnt |= (chip << 8) | REG_AUXSPICNT_CHIPSEL_Msk;

	for (size_t i = 0; i < nbytes; ++i) {
		hw->cnt = cnt | ((i < nbytes - 1 || cshold) ? AUX_SPICNT_CSHOLD_Msk : 0);

		if (txbuf) hw->data = txbuf[i];
		else hw->data = 0xff; // filler to start xferring a byte

		// wait until byte is xferred
		while (hw->cnt & REG_AUXSPICNT_BUSY_Msk) {
			COMPILER_BARRIER();
		}

		// get response
		if (rxbuf) rxbuf[i] = hw->data;
	}
}

