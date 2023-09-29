#ifndef _STORAGE_H_INCLUDED
#define _STORAGE_H_INCLUDED

#include <stdlib.h>

#define KEYSIZE 64
#define KEYLEN  (KEYSIZE - 1)

struct Mapping
{
	char key[KEYSIZE];
	short value;
};

struct Hashtable
{
	struct Mapping* memory;
	size_t maximum;
	size_t count;
};

void Hashtable_Init(struct Hashtable*);

void Hashtable_Free(struct Hashtable*);

void Hashtable_Add(struct Hashtable*, const char* key, short value);

short Hashtable_Lookup(struct Hashtable*, const char* key);

short Hashtable_Remove(struct Hashtable*, const char* key);

size_t Hashtable_Size(struct Hashtable*);

#endif // HASHTABLE_H_INCLUDED
