
extern Elf32_auxv_t* __crt0_auxv;

#define PARSE_STACK \
	static char *v[2] = {0}; \
	/* trick from sdk-seven: prevent LTO from inlining main() */ \
	asm(""::"X"(main)); \
	int argc; \
	char** argv; \
	char** envp; \
	if (ABI_HB_ARGV->magic == HB_ARGV_MAGIC) { \
		argc = ABI_HB_ARGV->argc; \
		argv = ABI_HB_ARGV->argv; \
		envp = &argv[argc/*theres an extra nullptr at the end of the array*/+1]; \
		char** envp2 = envp; \
		bool envp_valid = true; /* not always the case, sadly */ \
		/* look for end of envp array, past that lies auxv */ \
		for (size_t i = 0; *envp2; ++i, ++envp2) { \
			/* if envp is bogus, bail out */ \
			if (i >= 256 || (uintptr_t)*envp2 < 0x01000000 || (uintptr_t)*envp2 >= 0x10000000 || (uintptr_t)envp2 >= 0x03000000) { \
				envp_valid = false; \
				break; \
			} \
		} \
		if (!envp_valid) { \
			envp = &v[1]; \
			__crt0_auxv = NULL; \
		} else { \
			++envp2; \
			__crt0_auxv = (Elf32_auxv_t*)envp2; \
			if (__crt0_auxv[0].a_type != AT_IGNORE || \
					__crt0_auxv[0].a_un.a_val != ABI_AUXV_IGNORE_MAGIC) \
				__crt0_auxv = NULL; /* valid envp but invalid auxv */ \
		} \
	} else { \
		argc = 0; \
		argv = &v[0]; \
		envp = &v[1]; \
	} \

