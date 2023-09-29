#include <string.h>

#include "storage.h"

size_t Hashtable_Mod(struct Hashtable* ht, size_t index) {
	// mods the index against the maximum size of memory
	// optimization only works if maximum is a power of 2
	return (ht->maximum - 1) & index;
}

// dan bernstein's string hashing function
size_t Hash(struct Hashtable* ht, const char* key) {
	size_t hash = 5381;
	size_t length = strlen(key);
	if(length > KEYLEN) length = KEYLEN;
	for(size_t i = 0; i < length; i++) {
		hash = ((hash << 5) + hash) ^ key[i];
	}
	return Hashtable_Mod(ht, hash);
}

Mapping* Hashtable_FindMapping(struct Hashtable* ht, const char* key) {
	size_t index = Hashtable_Hash(ht, key);
	size_t start = index;
	while(strncmp(ht->memory[index].key, key, KEYLEN) != 0) {
		if(ht->memory[index].key[0] == '\0')
			return NULL;
		index++;
		if(index >= ht->maximum)
			index = 0;
		if(index == start)
			return NULL;
	}
	return ht->memory + index;
}

void Hashtable_Clear(struct Hashtable* ht) {
	for(size_t i = 0; i < ht->maximum; i++) {
		ht->memory[i].key[0] = '\0';
	}
}

void Hashtable_Expand(struct Hashtable* ht) {
	// save old storage values
	Mapping* oldMem = ht->memory;
	size_t oldMax = ht->maximum;
	// make new ones
	ht->maximum <<= 1;
	ht->memory = (Mapping*)malloc(sizeof(Mapping) * ht->maximum);
	Hashtable_Clear(ht);
	ht->count = 0;

        // must do a brute force copy since hash values will change with changing array size
        for(size_t i = 0; i < oldMax; i++) {
		if(*oldMem[i].key)
			Hashtable_Add(ht, oldMem[i].key, oldMem[i].value);
        }

        free( oldMem );
}

void Hashtable_Init(struct Hashtable* ht) {
	ht->maximum = 64;
	ht->memory = (short*)malloc( sizeof(short) * maximum );
}

void Hashtable_Free(struct Hashtable* ht) {
	free(ht->memory);
}

void Hashtable_Add(struct Hashtable* ht, const char* key, short value) {
	size_t index = Hashtable_Hash(ht, key);
	size_t start = index;
	while(ht->memory[index].key[0] != '\0' && strncmp(ht->memory[index].key, key, KEYLEN) != 0) {
		index++;
		if(index >= ht->maximum)
			index = 0;
		if(index == start) {
			Hashtable_Expand(ht);
			index = Hashtable_Hash(key);
			start = index;
		}
	}
	strncpy(ht->memory[index].key, key, KEYLEN);
	ht->memory[index].key[KEYLEN] = '\0';
	ht->memory[index].value = value;
	count++;
}

short Hashtable_Lookup(struct Hashtable* ht, const char* key) {
	Mapping* mapping = Hashtable_FindMapping(ht, key);
	if( mapping == NULL )
		return 0;
	return mapping->value;
}

short Hashtable_Remove(struct Hashtable* ht, const char* key) {
	Mapping* mapping = Hashtable_FindMapping(ht, key);
	short data = 0;
	if(mapping != NULL) {
		data = mapping->value;
		mapping->key[0] = '\0';
		ht->count--;
	}
	return data;
}

size_t Hashtable_Size(struct Hashtable* ht) {
	return ht->count;
}
