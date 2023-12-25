
#ifndef DAWN_HW_DSP_H_
#define DAWN_HW_DSP_H_

#ifndef ARM9
#error "The DSP is exclusive to the ARM9"
#endif

#include <stdint.h>
#include <stdbool.h>

#include <dawn/hw/dsp/regs.h>
#include <dawn/hw/dsp/struct.h>

/** Powers on the DSP. If the DSP was not powered before calling this, it will
 *  enter sleep mode. */
void dsp_poweron(void);
/**
 * Reset the A9-DSP interface and reset the DSP core, optionally making it
 * execute its reset vector.
 *
 * @param release let the DSP core out of reset before returning. Setting this
 *        to false will leave the DSP core in reset (i.e. disabled) state.
 * @param ie_pmask interrupt enable and semaphore irqmask flags. lower 16 bit
 *        represents bits 5..11 of DSP_PCFG, higher 16 bit goes to DSP_PMASK
 */
void dsp_reset(bool release, uint32_t ie_pmsk);
/** Power down the DSP again. */
void dsp_poweroff(void);

#endif

