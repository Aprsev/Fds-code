#pragma once

// AVL node structure
struct AvlNode{
    int data;
    struct AvlNode* left,*right;
    int height; // Height of the tree
};

// Define a tree as a pointer to a tree node
typedef struct AvlNode* AvlTree;

// AVL methods, whose function is presented as it names
AvlTree createAvlTree();
void deleteAvlTree(AvlTree tree);
void insertAvlNode(AvlTree* tree,int data);
void inorderTraverseAvlTree(AvlTree tree,int sum, void (*callback)(int,int));