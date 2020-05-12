//
//  fictionalcharacter.cpp
//  fisaDE-bst
//
//  Created by christophe on 14/03/2019.
//  Copyright © 2019 christophe. All rights reserved.
//

#include "fictionalcharacter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Loads a database from a file given its absolute path on the filesystem.
 *
 * @param filename An absolute path to an existing file on the filesystem. The existence of the file is not checked.
 * @return A pointer to the newly created fictionalcharacter#database.
 */
database* load(char* filename) {

    database* db = new database;
    db->size = 0;
    // count lines in the file
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;

        }
    }
    fclose(fp);
    
printf( "lignes : %d", lines);

    // create a static size array to hold fictional characters
    const int n = lines;
    db->table = new FictionalCharacter*[n];
    
    // re-read the file to parse each line and add them to the table
    FILE* csv = fopen(filename, "r");
    char line[1024];
    int i = 0;
    while (fgets(line, 1024, csv))
    {
        // let's point to the begining of the line
        char* current = line;
        
        // we look for the index of the first occurence of semi-column
        size_t field_len_name = strcspn(current, ";");
        // we allocate an empty string
        char* name = (char*)malloc(50);
        // we copy from "current" the first "field_len_name" characters into the "name" string
        strncpy(name, current, field_len_name);
        // do not forgot to end the string with \0 !
        name[field_len_name] = '\0';
        // prepare for the next value : point to the "field_len_name + 1" character in "line"
        current = &line[field_len_name + 1];
        
        // same process repeats for surname
        size_t field_len_surname = strcspn(current, ";");
        char* surname = (char*)malloc(50);
        strncpy(surname, current, field_len_surname);
        surname[field_len_surname] = '\0';
        current = &line[field_len_name + field_len_surname + 2];
        
        // same process repeats for booktitle
        size_t field_len_btitle = strcspn(current, ";");
        char* booktitle = (char*)malloc(50);
        strncpy(booktitle, current, field_len_btitle);
        booktitle[field_len_btitle] = '\0';
        current = &line[field_len_name + field_len_surname + field_len_btitle + 3];
        
        // same process repeats for age
        size_t field_len_age = strcspn(current, ";");
        char* age = (char*)malloc(50);
        strncpy(age, current, field_len_age);
        age[field_len_age] = '\0';
        
        // create a new fictional character and copy its field value
        FictionalCharacter* fc = new FictionalCharacter;
        fc->name = name;
        fc->surname = surname;
        fc->booktitle = booktitle;
        fc->age = atoi(age);
        
        // insert the fictional character into the table
        db->table[i] = fc;
        
        // increase the table size
        db->size = db->size + 1;
        
        // increment the line counter
	printf("Loading in line...\n");
        i++;

    }
    // close the opened file
    fclose(csv);
    
    return db;
}
