#pragma once
#include "../includes/avl.h"

// BST node structure
struct BstNode{
    int data;
    struct BstNode* left,*right;
};

// Defin3 a tree as a pointer to a tree node
typedef struct BstNode* BstTree;

// BST methods, whose function is presented as it names
BstTree createBstTree();
void deleteBstTree(BstTree tree);
int findEquation(BstTree tree1,BstTree tree2,int sum,AvlTree* ans);
void preorderTraverseBstTree(BstTree tree);