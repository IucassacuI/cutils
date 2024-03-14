#include <stdio.h>
#include <stdint.h>
#include "memory.h"
#include "array.h"

array arr_new(void){
	array arr;
	arr.ptr = (uint64_t *) mem_alloc(10 * sizeof(uint64_t));
	arr.sorted = 0;
	arr.top = 0;
	arr.iterator = 0;

	return arr;
}

array arr_insert(array arr, uint16_t pos, uint64_t elm){
	if(arr.top < pos){
		arr.ptr  = (uint64_t *) mem_ralloc((char *) arr.ptr, (pos + 1) * sizeof(uint64_t));
		arr.top = pos;
	}

	mem_at(arr.ptr, sizeof(uint64_t), pos) = elm;

	arr.top += arr.top == pos;

	arr.sorted = arr_sorted(arr);
	return arr;
}

uint64_t arr_at(array arr, uint16_t pos){
	if(pos > arr.top)
		return -1;

	return mem_at(arr.ptr, sizeof(uint64_t), pos);
}

uint64_t arr_next(array *arr){
	uint64_t elm = 0;

	if(arr->iterator < arr->top){
		elm = mem_at(arr->ptr, sizeof(uint64_t), arr->iterator);
		arr->iterator++;
	} else {
		arr->iterator = 0;
		elm = mem_at(arr->ptr, sizeof(uint64_t), 0);
	}

	return elm;
}

array arr_push(array arr, uint64_t elm){
	int size = arr_allocsize(arr);

	if(arr.top+1 > size)
		arr.ptr = (uint64_t *) mem_ralloc((char *) arr.ptr, (size+1) * sizeof(uint64_t));

	mem_at(arr.ptr, sizeof(uint64_t), arr.top) = elm;
	arr.top++;
	arr.sorted = arr_sorted(arr);

	return arr;
}

array arr_pop(array arr){
	mem_at(arr.ptr, sizeof(uint64_t), arr.top-1) = 0;
	arr.top--;

	return arr;
}

array arr_del(array arr, uint16_t pos){
	array newarr = arr_new();

	for(int i = 0; i < arr.top; i++){
		if(i == pos)
			continue;

		newarr = arr_push(newarr, arr.ptr[i]);
	}

	newarr.sorted = arr_sorted(newarr);
	return newarr;
}

array arr_shift(array arr){
	array newarr = arr_new();

	for(int i = 1; i < arr.top; i++){
		newarr = arr_push(newarr, mem_at(arr.ptr, sizeof(uint64_t), i));
	}

	return newarr;
}

array arr_unshift(array arr, uint64_t elm){
	array newarr = arr_new();

	newarr = arr_push(newarr, elm);

	for(int i = 0; i < arr.top; i++){
		newarr = arr_push(newarr, mem_at(arr.ptr, sizeof(uint64_t), i));
	}

	return newarr;
}

static int cmp(const void *a, const void *b){
	unsigned int num1 = *(const unsigned int *)a;
	unsigned int num2 = *(const unsigned int *)b;

	return num1-num2;
}

static int arr_linear(array arr, uint64_t elm){
	for(int j = 0; j < arr.top; j++){
		if(mem_at(arr.ptr, sizeof(uint64_t), j) == elm)
			return 1;
	}

	return 0;
}

static int arr_binary(array arr, uint64_t elm){
	return bsearch(&elm, arr.ptr, arr.top-1, sizeof(uint64_t), cmp) != NULL;
}

int arr_include(array arr, uint64_t elm){
	if(arr.sorted)
		return arr_binary(arr, elm);
	return arr_linear(arr, elm);
}

int arr_allocsize(array arr){
	int size = mem_query((char *) arr.ptr) / sizeof(uint64_t);

	return size;
}

int arr_size(array arr){
	return arr.top;
}

void arr_print(array arr){
	putchar('[');

	for(int k = 0; k < arr.top; k++){
       		printf("%lu", mem_at(arr.ptr, sizeof(uint64_t), k));

		if(k+1 < arr.top)
			printf(", ");
	}

	puts("]");
}

array arr_sort(array arr){
	if(arr.sorted)
		return arr;

	qsort(arr.ptr, arr.top, sizeof(uint64_t), cmp);
	arr.sorted = 1;
	return arr;
}


int arr_sorted(array arr){
	for(int i = 0; i < arr.top-1; i++){
		if(mem_at(arr.ptr, sizeof(uint64_t), i) > mem_at(arr.ptr, sizeof(uint64_t), i+1))
			return 0;
	}

	return 1;
}
