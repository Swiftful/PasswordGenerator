//
//  Generator.c
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include "Generator.h"

typedef struct {
    uint64_t state;
} ThreadRNG;

static inline uint64_t xorshift64(uint64_t* state) {
    uint64_t x = *state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return *state = x;
}

// Alternative implementation functions (kept for reference)
// GCD-based implementation (optimal for macOS/iOS)
void GenerateWithGCD(Model model, HashSet* set, char* charset, int charsetSize) {
    dispatch_queue_t queue = dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0);
    uint64_t baseSeed = ((uint64_t)time(NULL) << 16) ^ (uint64_t)getpid();
    
    dispatch_apply(model.count, queue, ^(size_t index) {
        // Thread-local random state
        static __thread ThreadRNG rng = {0};
        if (rng.state == 0) {
            rng.state = baseSeed ^ (uint64_t)pthread_self() ^ index;
        }
        
        // Allocate string buffer
        char* generated = malloc(model.length + 1);
        if (!generated) return;
        
        // Generate random string
        for (int i = 0; i < model.length; i++) {
            uint64_t rand_val = xorshift64(&rng.state);
            generated[i] = charset[rand_val % charsetSize];
        }
        generated[model.length] = '\0';
        
        // Add to set (thread-safe)
        HashSet_Add(set, generated);
        
        free(generated);
    });
}


void GenerateDirectWithGCD(Model model, HashSet* set, Resources resources) {
    // Build charset automatically
    char* charset = malloc(Digit_Size + Upper_Size + Lower_Size + Punk_Size + 1);
    if (!charset) return;
    
    int charsetSize = 0;
    if (model.isDigit) {
        memcpy(charset + charsetSize, resources.Digit, Digit_Size);
        charsetSize += Digit_Size;
    }
    if (model.isLetter && model.isUpper) {
        memcpy(charset + charsetSize, resources.Upper, Upper_Size);
        charsetSize += Upper_Size;
    }
    if (model.isLetter && model.isLower) {
        memcpy(charset + charsetSize, resources.Lower, Lower_Size);
        charsetSize += Lower_Size;
    }
    if (model.isPunk) {
        unsigned long punkLen = strlen(resources.Punk);
        memcpy(charset + charsetSize, resources.Punk, punkLen);
        charsetSize += punkLen;
    }
    charset[charsetSize] = '\0';
    
    if (charsetSize == 0) {
        free(charset);
        return;
    }
    
    GenerateWithGCD(model, set, charset, charsetSize);
    free(charset);
}
