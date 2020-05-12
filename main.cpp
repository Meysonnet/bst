//
//  main.cpp
//  fisaDE-bst
//
//  Created by christophe on 14/03/2019.
//  Copyright © 2019 christophe. All rights reserved.
//

#include <iostream>
#include "fictionalcharacter.h"
#include "bst.hpp"

int main(int argc, const char * argv[]) {
    
    // load the database
    printf("Loading database...\n");
    database* db = load("/home/user/bst/db.txt");
    printf("Done loading database (%d reccords).\n\n", db->size);
    // Output all values for the sake of manual control
    for (int i = 0; i < db->size; i++) {
        printf("Name = %s\n", db->table[i]->name );
        printf("Surname = %s\n", db->table[i]->surname );
        printf("Booktitle = %s\n", db->table[i]->booktitle );
        printf("Age = %d\n\n", db->table[i]->age );
    }
    
    // create the index on the table
    printf("Creating index...\n");
    Node* root = index(db);
    printf("Done creating index.\n");
    
    printf("Depth of the index is %d\n\n", get_depth(root));
    
    // querying a character based on its name in O(log(get_depth(root)) + O(1)
    const char* query = "Smiley";
    printf("Looking up %s in the index ...\n", query);
    int idx = lookup(root, "Smiley");
    if (idx < 0) {
        printf("%s was not found in the index", query);
    } else {
        printf("%s is located at index %d in the table, its infos are :\n", query, idx);
        FictionalCharacter* answer = db->table[idx];
        printf("Name = %s\n", answer->name );
        printf("Surname = %s\n", answer->surname );
        printf("Booktitle = %s\n", answer->booktitle );
        printf("Age = %d\n\n", answer->age );
    }
    printf("Done looking up %s in the index.\n\n", query);
    
    printf("Good bye.\n");
    
    return 0;
}
