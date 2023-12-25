
#ifndef DAWN_UTIL_PANIC_H_
#define DAWN_UTIL_PANIC_H_

__attribute__((__noreturn__, __format__(printf, 1, 2)))
void panic_base(const char* fmt, ...);


#define panic(fmt, ...) panic_base("[" __FILE__ ":%d] " fmt, __LINE__, #__VA_ARGS__)

#endif

