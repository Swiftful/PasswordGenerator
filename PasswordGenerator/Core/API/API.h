//
//  API.h
//  generatorC
//
//  Created by Xose on 30.08.25.
//

#ifndef API_h
#define API_h

#include <stdio.h>
#include "HashSet.h"
#include "Model.h"

int API(Model model);
double START(Model model, HashSet* hashset);
bool WRITE(const char* filename, HashSet* hashset);
bool EXIT(HashSet* set);

#endif /* API_h */
