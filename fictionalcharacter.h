//
//  fictionalcharacter.h
//  fisaDE-bst
//
//  Created by christophe on 14/03/2019.
//  Copyright © 2019 christophe. All rights reserved.
//

#ifndef fictionalcharacter_h
#define fictionalcharacter_h
#include <string.h>

using namespace std;
typedef struct {
    char* name;
    char* surname;
    char* booktitle;
    int age;
    
} FictionalCharacter;

typedef struct {
    FictionalCharacter** table;
    int size;
} database;

database* load(char* filename);

#endif /* fictionalcharacter_h */
