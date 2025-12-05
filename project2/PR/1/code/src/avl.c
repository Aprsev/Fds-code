#include "../includes/avl.h"
#include <stdlib.h>

// Create a new AVL tree
AvlTree createAvlTree() {
    AvlTree tree = (AvlTree)malloc(sizeof(struct AvlNode));
    if (tree == NULL) {
        return NULL;
    }
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1; // Initial height of a new node is 1
    return tree;
}

// Delete the AVL tree 
void deleteAvlTree(AvlTree tree) {
    if (tree != NULL) {
        // Delete its children first
        deleteAvlTree(tree->left);
        deleteAvlTree(tree->right);
        // Then delete the root 
        free(tree);
    }
}

// Calulate the height of the tree
void updateHeight(AvlTree tree) {
    if (tree != NULL) {
        // In case its children are NULL, set to 0
        int leftHeight = (tree->left != NULL) ? tree->left->height : 0;
        int rightHeight = (tree->right != NULL) ? tree->right->height : 0;
        // Set the height of the current node to the max height of its children + 1
        tree->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

// Rotate the tree to the left
void rotateLeft(AvlTree* tree) {
    if(tree != NULL) {
        AvlTree temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = *tree;
        *tree = temp;

        // Update the heights of the nodes after rotation
        updateHeight((*tree)->left);
        updateHeight(*tree);
    }
}

// Rotate the tree to the right
void rotateRight(AvlTree* tree) {
    if(tree != NULL){
        AvlTree temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = *tree;
        *tree = temp;

        // Update the heights of the nodes after rotation
        updateHeight((*tree)->right);
        updateHeight(*tree);
    }
}

int getFactor(AvlTree tree) {
    // Calculate the balance factor of the tree node
    if (tree == NULL || (tree->left == NULL && tree->right == NULL)) {
        return 0;
    }

    // Handle the case when one of the children is NULL
    if(tree->left == NULL) {
        return tree->right->height;
    } else if (tree->right == NULL) {
        return -tree->left->height;
    } else {
        // If both of its children exist, return the difference of their heights
        return tree->right->height - tree->left->height;
    }
}

// Balancing the AVL tree 
void balance(AvlTree* tree) {
    // Right heavy case
    if (getFactor(*tree) > 1) {
        if (getFactor((*tree)->right) < 0) {
            // RL case
            rotateRight(&(*tree)->right);
        }
        // LL case
        rotateLeft(tree);
    // Left heavy case
    } else if (getFactor(*tree) < -1) {
        if (getFactor((*tree)->left) > 0) {
            // LR case
            rotateLeft(&(*tree)->left);
        }
        // RR case
        rotateRight(tree);
    }
}

// Insert node into AVL tree
// Didn't indert the node if it already exists in the tree
void insertAvlNode(AvlTree* tree, int data) {
    if (*tree == NULL) {
        // Create a new node if encounters leaf
        *tree = createAvlTree();
        if (*tree == NULL) {
            return;
        }
        (*tree)->data = data;
        return;
    }
    
    // If greater, search right subtree recursively
    if (data < (*tree)->data) {
        insertAvlNode(&(*tree)->left, data);
    // If smaller, search left subtree recursively
    } else if (data > (*tree)->data) {
        insertAvlNode(&(*tree)->right, data);
    } 
    // If equal, do nothing (no duplicates allowed)
    else {
        return;
    }

    // Update the height of the current node
    updateHeight(*tree);

    // Balancing the tree after insertion
    balance(tree);
}

void inorderTraverseAvlTree(AvlTree tree,int sum, void (*callback)(int,int)) {
    // Traverse the tree in order 
    if (tree != NULL) {
        inorderTraverseAvlTree(tree->left,sum, callback);
        // Callback to output the equation
        callback(sum,tree->data);
        inorderTraverseAvlTree(tree->right,sum, callback);
    }
}