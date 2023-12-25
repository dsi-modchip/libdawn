
#include <stdlib.h>

#include <dawn/util/panic.h>

void panic_base(const char* fmt, ...) {
	(void)fmt; // TODO: print somehow
	abort();
}

