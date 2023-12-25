
#include <sys/auxv.h>

Elf32_auxv_t* __crt0_auxv;

unsigned long getauxval(unsigned long type) {
	for (Elf32_auxv_t* p = __crt0_auxv; p->a_type != AT_NULL; ++p) {
		if (p->a_type == type) return p->a_un.a_val;
	}

	return 0; // not found
}


