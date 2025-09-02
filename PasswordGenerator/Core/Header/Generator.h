//
//  Generator.h
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#ifndef Generator_h
#define Generator_h

#include "Model.h"
#include "HashSet.h"
#include "Resources.h"

#define MAX_LEN 1024

void GenerateWithGCD(Model model, HashSet* set, char* charset, int charsetSize);
void GenerateDirectWithGCD(Model model, HashSet* set, Resources resources);

#endif /* Generator_h */
