//
//  Resources.h
//  generatorC
//
//  Created by Xose on 28.08.25.
//

#ifndef Resources_h
#define Resources_h

#define Digit_Size 10
#define Upper_Size 26
#define Lower_Size 26
#define Punk_Size 32

typedef struct Resources {
    char Digit[Digit_Size + 1];
    char Upper[Upper_Size + 1];
    char Lower[Lower_Size + 1];
    char Punk[Punk_Size + 1];
} Resources;

Resources Resources_Init(void);

#endif /* Resources_h */
