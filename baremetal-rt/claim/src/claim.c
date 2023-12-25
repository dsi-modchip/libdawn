
#include <assert.h>

#include <dawn/util/panic.h>
#include <dawn/hw/arm.h>

#include <dawn/baremetal-rt/claim.h>

bool claim_is_claimed(claim_bits_t* bits, uint32_t bit) {
	return *bits & (1u << bit);
}

void claim_or_assert(claim_bits_t* bits, uint32_t bit, const char* msg) {
	CRITICAL_SECTION({
		if (claim_is_claimed(bits, bit)) panic("Required %s %lu already in use!\n", msg, bit);
		else *bits |= 1u << bit;
	});
}

int claim_unused_from_range(claim_bits_t* bits, bool req, uint32_t lsb, uint32_t msb, const char* msg) {
	int found_bit = -1;

	CRITICAL_SECTION({
		for (uint32_t bit = lsb; bit <= msb; ++bit) {
			if (!claim_is_claimed(bits, bit)) {
				*bits |= 1u << bit;
				found_bit = bit;
				break;
			}
		}
	});

	if (found_bit < 0 && req) panic("All %s exhausted!\n", msg);

	return found_bit;
}
void claim_clear(claim_bits_t* bits, uint32_t bit) {
	CRITICAL_SECTION({
		assert(claim_is_claimed(bits, bit));
		*bits &= ~(uint32_t)(1u << bit);
	});
}

