#include "../includes/bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Get user input and create the tree
BstTree createBstTree() {
    BstTree tree = NULL;
    int n;
    scanf("%d", &n);
    // Since we know the number of nodes, we can use an array to point to all nodes
    BstTree* treeNodes = (BstTree*)malloc(sizeof(BstTree*) * n);
    // As well to its parent index
    int* parentIndex = (int*)malloc(sizeof(int) * n);
    if (treeNodes == NULL) {
        return tree; 
    }
    // Read inputs, allocating memory
    // I don't allocate the memory at once, that's mainly because it cause error when releasing the memory, I don't know the first node's address
    for (int i = 0;i < n;i++){
        // Allocating memory for each node
        treeNodes[i] = (BstTree)malloc(sizeof(struct BstNode));
        scanf("%d%d", &treeNodes[i]->data, &parentIndex[i]);
        treeNodes[i]->left = NULL;
        treeNodes[i]->right = NULL;
    }
    for (int i = 0;i < n;i++){
        // If the parent index is -1, set the node as the root of the tree
        if (parentIndex[i] == -1){
            tree = treeNodes[i];
        }else{
            // If not, set the node as a child of its parent
            // Comparing data to determine if it is a left or right child
            if (treeNodes[i]->data < treeNodes[parentIndex[i]]->data){
                treeNodes[parentIndex[i]]->left = treeNodes[i];
            }else{
                treeNodes[parentIndex[i]]->right = treeNodes[i];
            }
        }
    }
    return tree;
}

// Delete the tree
void deleteBstTree(BstTree tree){
    if(tree->left != NULL) deleteBstTree(tree->left);
    if(tree->right != NULL) deleteBstTree(tree->right);
    free(tree);
}

// Traverse the tree in preorder
void preorderTraverseBstTree(BstTree tree){
    if (tree == NULL) return;
    printf("%d ", tree->data);
    preorderTraverseBstTree(tree->left);
    preorderTraverseBstTree(tree->right);
}

// Helper function to count nodes in a BST
int countNodes(BstTree tree) {
    if (tree == NULL) return 0;
    return 1 + countNodes(tree->left) + countNodes(tree->right);
}

// Helper function to convert BST to sorted array using inorder traversal
void bstToArray(BstTree tree, int* array, int* index) {
    if (tree == NULL) return;
    bstToArray(tree->left, array, index);
    array[(*index)++] = tree->data;
    bstToArray(tree->right, array, index);
}

// Find the equation in the two trees using array-based approach
int findEquation(BstTree tree1, BstTree tree2, int sum, AvlTree* ans) {
    // Count nodes in both trees
    int size1 = countNodes(tree1);
    int size2 = countNodes(tree2);
    
    if (size1 == 0 || size2 == 0) return 0;
    
    // Allocate arrays for both trees
    int* array1 = (int*)malloc(size1 * sizeof(int));
    int* array2 = (int*)malloc(size2 * sizeof(int));
    
    // Convert trees to arrays
    int index1 = 0, index2 = 0;
    bstToArray(tree1, array1, &index1);
    bstToArray(tree2, array2, &index2);

    int left = 0;
    int right = size2 - 1;
    int found = 0;
    
    while (left < size1 && right >= 0) {
        int current_sum = array1[left] + array2[right];
        
        if (current_sum == sum) {
            // Found a pair, insert into set
            insertAvlNode(ans, array1[left]);
            found = 1;
            left++;
            right--;
        } else if (current_sum < sum) {
            left++;  // Need larger value from array1
        } else {
            right--; // Need smaller value from array2
        }
    }
    
    // Release allocated memory
    free(array1);
    free(array2);
    
    return found;
}