#include <stdio.h>
#include <stdlib.h>
#include "./includes/bst.h"
#include "./includes/avl.h"

// Callback function to print the equation
void printResult(int sum,int data) {
    printf("%d = %d + %d\n", sum, data, sum - data);
}

int main(){
    // Create two BST trees
    BstTree tree1 = createBstTree();
    BstTree tree2 = createBstTree();

    // Get the equation sum
    int sum;
    scanf("%d",&sum);

    // The AVL tree worked as a set, to ensure that the result is unique
    AvlTree ans = NULL;

    // Find all solution satisfying the equation
    int res = findEquation(tree1, tree2, sum, &ans);
    if(!res) // No solution is found
        printf("false\n");
    else printf("true\n");

    // Traverse the AVL tree and print the equation
    inorderTraverseAvlTree(ans,sum, printResult);

    // Traverse the tree in preorder
    preorderTraverseBstTree(tree1);
    printf("\n");
    preorderTraverseBstTree(tree2);
    printf("\n");

    // Free the memory 
    deleteBstTree(tree1);
    deleteBstTree(tree2);
    return 0;
}