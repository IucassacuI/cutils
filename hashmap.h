#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct bucket {
	char *key;
	uint64_t value;
} bucket;

typedef struct hashmap {
	bucket **buckets;
	uint32_t size;
} hashmap;

hashmap  hash_new(void);
void     hash_set(hashmap hm, char *key, uint64_t value);
uint64_t hash_get(hashmap hm, char *key);
void     hash_del(hashmap hm, char *key);

#endif
