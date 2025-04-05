#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static char **mem_buffers;
static int *mem_bufsizes;

static int mem_size = 0;
static int sem = 1;

void mem_init(void){
	mem_buffers = calloc(2, sizeof(char *));
	mem_bufsizes = calloc(2, sizeof(int));

	assert(mem_buffers != NULL);
	assert(mem_bufsizes != NULL);
	mem_size = 2;
}

char *mem_alloc(int bytes){
	while(sem == 0){}
	sem--;

	char *ptr = calloc(bytes+1, sizeof(char));
	assert(ptr != NULL);

	for(int i = 0; i < mem_size; i++){
		if(mem_buffers[i] == NULL){
			mem_buffers[i] = ptr;
			mem_bufsizes[i] = bytes;

			sem++;
		   	return ptr;
		}
	}

	mem_size++;

	mem_buffers = realloc(mem_buffers, sizeof(char *)*mem_size);
	mem_bufsizes = realloc(mem_bufsizes, sizeof(int)*mem_size);

	assert(mem_buffers != NULL);
	assert(mem_bufsizes != NULL);

	mem_buffers[mem_size-1] = ptr;
	mem_bufsizes[mem_size-1] = bytes;

	sem++;

	return ptr;
}

char *mem_ralloc(char *ptr, int bytes){
	while(sem == 0){}

	int pos = 0;

	for(int j = 0; j < mem_size; j++){
		if(mem_buffers[j] == ptr){
			pos = j;
			break;
		}
	}

	char *new = realloc(ptr, bytes+1);
	assert(new != NULL);

	new[bytes] = 0;

	mem_buffers[pos] = new;
	mem_bufsizes[pos] = bytes;

	return new;
}

void mem_freeall(bool dealloc){
	while(sem == 0){}

	for(int k = 0; k < mem_size; k++){
		if(mem_buffers[k] != NULL){
			free(mem_buffers[k]);
			mem_buffers[k] = NULL;
			mem_bufsizes[k] = 0;
	        }
	}

	if(dealloc){
		free(mem_buffers);
		free(mem_bufsizes);
		mem_size = 0;
	}
}

void mem_copy(char *dst, const char *src){
	while(sem == 0){}

	int pos = -1;

	for(int l = 0; l < mem_size; l++){
		if(mem_buffers[l] == dst){
			pos = l;
			break;
		}
	}

	if(pos == -1)
		return;

	int dstsize = mem_bufsizes[pos];

	int m = 0;
	while(m < dstsize-1 && src[m] != 0){
		dst[m] = src[m];
		m++;
	}
	dst[m] = 0;
}


int mem_read(char *dst, FILE *src){
	while(sem == 0){}

	int pos = -1;

	for(int m = 0; m < mem_size; m++){
		if(mem_buffers[m] == dst){
			pos = m;
			break;
		}
	}

	if(pos == -1)
		return 0;

	char *ret = fgets(dst, mem_bufsizes[pos]-1, src);

	return ret != NULL;
}

int mem_query(const void *buffer){
	while(sem == 0){}
	int pos = -1;

	for(int n = 0; n < mem_size; n++){
		if(mem_buffers[n] == buffer){
			pos = n;
			break;
		}
	}

	if(pos == -1)
		return 0;
	else
		return mem_bufsizes[pos];
}
