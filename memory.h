#ifndef CUTILS_MEMORY
#define CUTILS_MEMORY

#include <stdbool.h>
#include <stdio.h>
#include <signal.h>

#define mem_at(addr, x, y) addr[y < mem_query((char *) addr)/x && y >= 0 ? y : raise(SIGABRT)]

void mem_init(void);
void mem_freeall(bool dealloc);
char *mem_alloc(int bytes);
char *mem_ralloc(char *ptr, int bytes);
void mem_copy(char *dst, const char *src);
int mem_read(char *dst, FILE *src);
int mem_query(const void *buffer);

#endif
