//
//  bst.cpp
//  fisaDE-bst
//
//  Created by christophe on 23/03/2019.
//  Copyright © 2019 christophe. All rights reserved.
//


#include <stdlib.h>

#include "bst.hpp"
#include "utils.hpp"

/**
 * Inserts a key/value pair into a bst.
 *
 * @param current the root of the BST where the insertion takes place
 * @param key the key of the element to insert
 * @param value the value to insert for the given key
 * @return true if the insertion was made, false otherwise (e.g. key/value already exists)
 */
bool insert (Node** current, const char* key, int value) {
    
    // if current is null pointer, we went down to a leave safe for insertion
    if (*current == nullptr) {
        *current = (Node*) malloc(sizeof(Node));
        (*current)->key = key;
        (*current)->table_rank = value;
        (*current)->left = nullptr;
        (*current)->right = nullptr;
        return true;
    }
    
    // otherwise, let's move left or right
    if (strcmp(key, (*current)->key) < 0) { // key is lower, go to left subtree
        return insert( &(*current)->left, key, value);
    }
    
    if (strcmp(key, (*current)->key) > 0) { // key is higher, go to right subtree
        return insert( &(*current)->right, key, value);
    }
    
    // k == v.key() : duplicated key !
    printf("%s is a duplicate (index already contains %s). It won't be inserted.\n", key, (*current)->key);
    return current;
    
}

/**
 * Check that a given tree is a BST.
 * To this end, we check in each node if the direct left child key is lower
 * than the node's key, and the direct right child key is higher than the node's key.
 *
 * @param node the root node of the tree to check
 * @return true if the tree is a bianry search tree, false otherwise.
 */
bool is_bst (Node* node) {
    
    // if node is null, we answer true for the current node (nothing to check)
    if (node == nullptr) {
        return true;
    }
        
    // if the left child exists and its key is higher than the node's one, it is not a BST
    if (node->left != nullptr && node->left->key > node->key) {
        return false;
    }
        
    // if the right child exists and its key is lower than the node's one, it is not a BST
    if (node->right != nullptr && node->right->key < node->key) {
        return false;
    }
    
    // call recursively for left and right subtree
    if (!is_bst(node->left) || !is_bst(node->right)) {
        return false;
    }
    
    // If we did not returned a false and end up here : all node verify the constraints, that is a BST.
    return true;

}

/**
 * Compite the depth (= height) of a binary search tree as the number of nodes in the longest path from the root to a leaf.
 * To do this, we will use recursion : call the function for the left and right subtree. When we reach a leaf,
 * we return 0. When both left and right subtree from a node are processed, we send back the maximum height
 * between the left subtree and the rightsubtree, adding one for the current node.
 */
int get_depth(Node* node) {
    
    // if this is a leaf, height is 0.
    if (node == nullptr) {
        return 0;
    }
    
    // recursive call for the depth of each subtree
    int left_depth = get_depth(node->left);
    int right_depth = get_depth(node->right);
    
    // Get the larger one and add 1 for the current node.
    if (left_depth > right_depth) {
        return (left_depth + 1);
    }
    else {
        return (right_depth + 1);
    }

}


/**
 * Create the BST index of the table from a database.
 *
 * @param db the database containing the fictional character table
 * @return the root of the newly created BST that is an index of the database table.
 */
Node* index(database* db) {
    
    // create a root node
    Node* root = nullptr;
    
    // shuffle the data
    FictionalCharacter** data = db->table;
    shuffle(data, (size_t) db->size);
    
    // iterate over all reccord in the database table
    for (int i = 0; i < db->size; i++) {
        if (insert(&root, db->table[i]->name, i)) {
            printf("Successfully indexed %s\n", db->table[i]->name);
        } else {
            printf("Cannot index %s\n", db->table[i]->name);
        }
    }
    
    return root;
}

/**
 * Lookup the value for the given key.
 *
 * @param root the root of the index where we will search the key
 * @param key the given key to search
 * @return int the value associated to the given key. Returns -1 if the value was not found.
 *
 */
int lookup(Node* node, const char* key) {
    if (node == nullptr) {
        return -1;
    }
    
    if (strcmp(key,node->key) < 0) {
        return lookup(node->left, key);
    }
    else if (strcmp(key,node->key) > 0) {
        return lookup(node->right, key);
    } else {
        return node->table_rank;
    }
    
}
