#ifndef BST_H
#define BST_H

#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a BST node
typedef struct Node {
    long long key; // Key value of the node
    struct Node *left; // Pointer to the left child
    struct Node *right; // Pointer to the right child
} Node;

// Function prototypes for tree operations
Node* construct_bst(long long* values, int* parent_indices, int n); // Construct a BST from values and parent indices
bool search_bst(Node* root, long long target); // Search for a target value in the BST
void find_pairs(Node* t1, Node* t2, long long target, long long** solutions, int* solution_count); // Find pairs of values from two BSTs that sum to a target
void sort_solutions(long long** solutions, int count); // Sort an array of pairs in ascending order
void print_preorder(Node* root, int i); // Print the preorder traversal of the BST
void free_tree(Node* root); // Free all memory allocated for the BST

#endif