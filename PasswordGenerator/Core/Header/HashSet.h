//
//  HashSet.h
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#ifndef HashSet_h
#define HashSet_h

#include <stdbool.h>
#include <pthread.h>

#define TABLE_SIZE 65536

typedef struct Node {
    char* key;
    struct Node* next;
} Node;

typedef struct HashSet {
    struct Node* table[TABLE_SIZE];
    pthread_mutex_t mutex;
    size_t size;
} HashSet;


HashSet* HashSet_Init(void);
bool HashSet_Add(HashSet* set, const char* key);
bool HashSet_Contains(HashSet* set, const char* key);
void HashSet_Free(HashSet* set);

#endif /* HashSet_h */
