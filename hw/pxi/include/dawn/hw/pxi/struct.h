
#ifndef DAWN_HW_PXI_STRUCT_H_
#define DAWN_HW_PXI_STRUCT_H_

#include <stdint.h>

#include <dawn/hw/iobase.h>


struct pxi_hw {
	uint16_t sync;
	uint16_t _pad0;
	uint16_t fifocnt;
	uint16_t _pad1;
	uint32_t fifosend;
	uint8_t _pad[0xffe80-0xc];
	uint32_t fiforecv;
};


#define REG_PXI_HW  (*(volatile struct pxi_hw*)IO_PXI_BASE)
#define REG_IPC_HW  (*(volatile struct pxi_hw*)IO_PXI_BASE)
#define REG_FIFO_HW (*(volatile struct pxi_hw*)IO_PXI_BASE)

#endif

