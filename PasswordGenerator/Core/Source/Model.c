//
//  Model.c
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#include "Model.h"

Model Model_Init(int length, int count, bool isLetter, bool isUpper, bool isLower, bool isPunk, bool isDigit) {
    Model model = {0};
    
    if (length > 0 && count > 0) {
        model.length = length;
        model.count = count;
    }
    
    model.isLetter = isLetter;
    model.isUpper = isUpper;
    model.isLower = isLower;
    model.isPunk = isPunk;
    model.isDigit = isDigit;
    
    return model;
}
