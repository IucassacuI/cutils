#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char **freearr;
static unsigned int *bufsizes;

static int size = 0;

void mem_init(void){
	freearr = calloc(2, sizeof(char *));
	bufsizes = calloc(2, sizeof(unsigned int));

	assert(freearr != NULL);
	assert(bufsizes != NULL);
	size = 2;
}

char *mem_alloc(unsigned int bytes){
	char *ptr = calloc(bytes, sizeof(char));
	assert(ptr != NULL);

	for(int i = 0; i < size; i++){
		if(freearr[i] == NULL){
			freearr[i] = ptr;
			bufsizes[i] = bytes;
		   	return ptr;
		}
	}

	size++;

	freearr = realloc(freearr, sizeof(char *)*size);
	bufsizes = realloc(bufsizes, sizeof(unsigned int)*size);

	assert(freearr != NULL);
	assert(bufsizes != NULL);

	freearr[size-1] = ptr;
	bufsizes[size-1] = bytes;

	return ptr;
}

char *mem_ralloc(char *ptr, unsigned int bytes){
	int pos = 0;

	for(int j = 0; j < size; j++){
		if(freearr[j] == ptr){
			pos = j;
			break;
		}
	}

	char *new = realloc(ptr, bytes);
	assert(new != NULL);

	freearr[pos] = new;
	bufsizes[pos] = bytes;

	return new;
}

void mem_freeall(bool dealloc){
	for(int k = 0; k < size; k++){
		if(freearr[k] != NULL){
			free(freearr[k]);
			freearr[k] = NULL;
			bufsizes[k] = 0;
	        }
	}

	if(dealloc){
		free(freearr);
		free(bufsizes);
		size = 0;
	}
}

void mem_copy(char *dst, const char *src){
	int pos = -1;

	for(int l = 0; l < size; l++){
		if(freearr[l] == dst){
			pos = l;
			break;
		}
	}

	if(pos == -1)
		return;

	int dstsize = bufsizes[pos];

	for(int m = 0; m < dstsize-1 && src[m] != 0; m++)
		dst[m] = src[m];
}


int mem_read(char *dst, FILE *src){
	int pos = -1;

	for(int m = 0; m < size; m++){
		if(freearr[m] == dst){
			pos = m;
			break;
		}
	}

	if(pos == -1)
		return 0;

	char *ret = fgets(dst, bufsizes[pos]-1, src);

	return ret != NULL;
}

int mem_query(const char *buffer){
	int pos = -1;

	for(int n = 0; n < size; n++){
		if(freearr[n] == buffer){
			pos = n;
			break;
		}
	}

	if(pos == -1)
		return 0;
	else
		return bufsizes[pos];
}
