#ifndef CUTILS_MEMORY
#define CUTILS_MEMORY
#include <stdbool.h>
#include <stdio.h>

void mem_init(void);
void mem_freeall(bool dealloc);
char *mem_alloc(unsigned int bytes);
char *mem_ralloc(char *ptr, unsigned int bytes);
void mem_copy(char *dst, const char *src);
int mem_read(char *dst, FILE *src);
int mem_query(const char *buffer);

#endif
