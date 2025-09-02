//
//  API.c
//  generatorC
//
//  Created by Xose on 30.08.25.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Generator.h"

#define BUFFER_SIZE 1<<20

int API(Model model){
    if (model.length <= 0 || model.count <= 0 || model.length > MAX_LEN){ return -1; }
    return 1;
}

double START(Model model, HashSet* hashset) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    GenerateDirectWithGCD(model, hashset, Resources_Init());
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) / 1000000000.0;
}


bool WRITE(const char* filename, HashSet* hashset) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return false;
    }

    char* buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        perror("malloc");
        fclose(f);
        return false;
    }

    size_t buf_len = 0;

    for (size_t i = 0; i < TABLE_SIZE; i++) {
        Node* node = hashset->table[i];
        while (node) {
            size_t key_len = strlen(node->key);
            
            if (buf_len + key_len + 1 >= BUFFER_SIZE) {
                fwrite(buffer, 1, buf_len, f);
                buf_len = 0;
            }
            
            memcpy(buffer + buf_len, node->key, key_len);
            buf_len += key_len;
            buffer[buf_len++] = '\n';
            node = node->next;
        }
    }

    if (buf_len > 0) { fwrite(buffer, 1, buf_len, f); }
    free(buffer);
    fclose(f);
    return true;
}

bool EXIT(HashSet* set){
    HashSet_Free(set);
    return true;
}
