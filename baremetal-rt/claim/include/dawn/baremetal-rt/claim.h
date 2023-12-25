
#ifndef DAWN_BAREMETALRT_CLAIM_H_
#define DAWN_BAREMETALRT_CLAIM_H_

#include <stdint.h>
#include <stdbool.h>

/* don't have more than 16 of anything so this is fine
 * (4 DMA, 4 NDMA, 4 timer, 16 sound channels)
 * (N)WRAM, VRAM, sprites, etc. should use a more complicated allocator
 */
typedef uint16_t claim_bits_t;

void claim_or_assert(claim_bits_t* bits, uint32_t bit, const char* msg);
int claim_unused_from_range(claim_bits_t* bits, bool req, uint32_t lsb, uint32_t msb, const char* msg);
bool claim_is_claimed(claim_bits_t* bits, uint32_t bit);
void claim_clear(claim_bits_t* bits, uint32_t bit);

#endif

