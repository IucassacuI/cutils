#ifndef CUTILS_ARR
#define CUTILS_ARR

#include <stdint.h>

typedef struct {
	uint64_t *ptr;
	int top;
	int sorted;
	int iterator;
} array;

array    arr_new(void);
int      arr_allocsize(array arr);
int      arr_size(array arr);
array    arr_insert(array arr, uint16_t pos, uint64_t elm);
uint64_t arr_at(array arr, uint16_t pos);
uint64_t arr_next(array *arr);
int      arr_include(array arr, uint64_t elm);
array    arr_push(array arr, uint64_t elm);
array    arr_pop(array arr);
array    arr_del(array arr, uint16_t pos);
array    arr_shift(array arr);
array    arr_unshift(array arr, uint64_t elm);
array    arr_sort(array arr);
int      arr_sorted(array arr);

#endif
