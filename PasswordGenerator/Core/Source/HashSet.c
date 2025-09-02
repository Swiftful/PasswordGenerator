//
//  HashSet.c
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "HashSet.h"


static unsigned int Hash(const char* key) {
    unsigned int hash = 2166136261U;
    while (*key) {
        hash ^= (unsigned char)*key++;
        hash *= 16777619;
    }
    return hash % TABLE_SIZE;
}

HashSet* HashSet_Init(void) {
    HashSet* set = calloc(1, sizeof(HashSet));
    if (!set) return NULL;
    
    if (pthread_mutex_init(&set->mutex, NULL) != 0) {
        free(set);
        return NULL;
    }
    
    set->size = 0;
    return set;
}

bool HashSet_Add(HashSet* set, const char* key) {
    if (!set || !key) return false;
    
    unsigned int idx = Hash(key);
    size_t keyLen = strlen(key);
    
    pthread_mutex_lock(&set->mutex);
    
    Node* current = set->table[idx];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            pthread_mutex_unlock(&set->mutex);
            return false;
        }
        current = current->next;
    }
    
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        pthread_mutex_unlock(&set->mutex);
        return false;
    }
    
    new_node->key = malloc(keyLen + 1);
    if (!new_node->key) {
        free(new_node);
        pthread_mutex_unlock(&set->mutex);
        return false;
    }
    
    memcpy(new_node->key, key, keyLen + 1);
    new_node->next = set->table[idx];
    set->table[idx] = new_node;
    set->size++;
    
    pthread_mutex_unlock(&set->mutex);
    return true;
}

bool HashSet_Contains(HashSet* set, const char* key) {
    if (!set || !key) return false;
    
    unsigned int idx = Hash(key);
    
    pthread_mutex_lock(&set->mutex);
    Node* current = set->table[idx];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            pthread_mutex_unlock(&set->mutex);
            return true;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&set->mutex);
    return false;
}


void HashSet_Free(HashSet* set) {
    if (!set) return;
    
    pthread_mutex_lock(&set->mutex);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = set->table[i];
        while (current) {
            Node* tmp = current;
            current = current->next;
            free(tmp->key);
            free(tmp);
        }
    }
    pthread_mutex_unlock(&set->mutex);
    pthread_mutex_destroy(&set->mutex);
    free(set);
}
