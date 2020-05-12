//
//  bst.hpp
//  fisaDE-bst
//
//  Created by christophe on 23/03/2019.
//  Copyright © 2019 christophe. All rights reserved.
//

#ifndef bst_hpp
#define bst_hpp

#include <stdio.h>
#include "fictionalcharacter.h"

typedef struct Node {
    const char* key;
    int table_rank;
    Node* left;
    Node* right;
} Node;

bool insert (Node** current, const char* key, int value);
bool is_bst (Node* node);
int get_depth (Node* node);
Node* index(database* db);
int lookup(Node* root, const char* key);

#endif /* bst_hpp */
