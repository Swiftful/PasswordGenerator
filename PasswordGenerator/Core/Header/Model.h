//
//  Model.h
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#ifndef Model_h
#define Model_h

#include <stdbool.h>

typedef struct Model {
    int length;
    int count;
    bool isLetter;
    bool isUpper;
    bool isLower;
    bool isPunk;
    bool isDigit;
} Model;

Model Model_Init(int length, int count, bool isLetter, bool isUpper, bool isLower, bool isPunk, bool isDigit);
#endif
