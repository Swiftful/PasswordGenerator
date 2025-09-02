//
//  Resources.c
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#include <string.h>
#include "Resources.h"

Resources Resources_Init(void) {
    Resources resources;
    
    for (int i = 0; i < Digit_Size; i++) {
        resources.Digit[i] = '0' + i;
    }
    resources.Digit[Digit_Size] = '\0';
    
    for (int i = 0; i < Upper_Size; i++) {
        resources.Upper[i] = 'A' + i;
    }
    resources.Upper[Upper_Size] = '\0';
    
    for (int i = 0; i < Lower_Size; i++) {
        resources.Lower[i] = 'a' + i;
    }
    resources.Lower[Lower_Size] = '\0';
    
    const char specialChars[] = "!@#$%^&*()_+-=[]{}|;:',.<>?/~`";
    int specialLen = strlen(specialChars);
    int copyLen = (specialLen < Punk_Size) ? specialLen : Punk_Size;
    
    memcpy(resources.Punk, specialChars, copyLen);
    resources.Punk[copyLen] = '\0';
    
    return resources;
}
