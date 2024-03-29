#include <string.h>
#include <stdint.h>
#include "hashmap.h"
#include "memory.h"

static uint32_t djb_hash(char *str){
	uint32_t hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;

	return hash;
}

hashmap hash_new(void){
	hashmap hm;
	hm.buckets = (bucket **) mem_alloc(10 * sizeof(bucket));
	hm.size = 9;

	return hm;
}

void hash_set(hashmap hm, char *key, uint64_t value){
	uint32_t pos = djb_hash(key) % hm.size;

	if(mem_at(hm.buckets, sizeof(bucket *), pos) != NULL){
		hm.size++;
		pos = djb_hash(key) % hm.size;
		hm.buckets = (bucket **) mem_ralloc((char *) hm.buckets, hm.size * sizeof(bucket));
	}

	char *copy = mem_alloc(strlen(key) + 1);
	mem_copy(copy, key);

	bucket *b = (bucket *) mem_alloc(sizeof(bucket));
	b->key = copy;
	b->value = value;

	mem_at(hm.buckets, sizeof(bucket *), pos) = b;
}

uint64_t hash_get(hashmap hm, char *key){
	uint32_t pos = djb_hash(key) % hm.size;
	bucket *b = mem_at(hm.buckets, sizeof(bucket *), pos);

	if(b == NULL)
		return 0;

	if(strcmp(key, b->key) != 0){
		for(uint32_t i = 0; i < hm.size; i++){
			b = mem_at(hm.buckets, sizeof(bucket *), i);

			if(b == NULL)
				continue;
			else if(strcmp(key, b->key) == 0)
				return b->value;
		}
	}

	return b->value;
}

void hash_del(hashmap hm, char *key){
	uint32_t pos = djb_hash(key) % hm.size;

	if(mem_at(hm.buckets, sizeof(bucket *), pos) == NULL)
		return;

	if(strcmp(hm.buckets[pos]->key, key) != 0)
		return;

	mem_at(hm.buckets, sizeof(bucket *), pos) = NULL;
}
