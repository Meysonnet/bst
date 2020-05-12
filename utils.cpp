//
//  utils.cpp
//  fisaDE-bst
//
//  Created by christophe on 23/03/2019.
//  Copyright © 2019 christophe. All rights reserved.
//

#include "utils.hpp"
#include <stdlib.h>

/**
 * Shuffling an array of data.
 * More than inspired from : https://benpfaff.org/writings/clc/shuffle.html
 */
void shuffle(FictionalCharacter** data, size_t size) {
    if (size > 1)
    {
        size_t i;
        for (i = 0; i < size - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            FictionalCharacter* t = data[j];
            data[j] = data[i];
            data[i] = t;
        }
    }
}
