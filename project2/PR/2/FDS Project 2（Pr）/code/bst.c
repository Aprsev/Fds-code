#include "bst.h"

int flag_scope[2] = {0}; // Global variable to control the output format

// Function to construct a BST from values and parent indices
Node* construct_bst(long long* values, int* parent_indices, int n)
{
    // Allocate memory for all nodes
    Node** nodes = (Node**)malloc(n * sizeof(Node*));
    // Return NULL if memory allocation fails
    if (!nodes) 
        return NULL;
    
    // Initialize all nodes
    for (int i = 0; i < n; i++)
    {
        nodes[i] = (Node*)malloc(sizeof(Node));
        if (!nodes[i])
        {
            // Free previously allocated memory
            for (int j = 0; j < i; j++)
                free(nodes[j]);
            free(nodes);
            return NULL;
        }
        nodes[i]->key = values[i]; // Assign the key value
        nodes[i]->left = NULL; // Initialize left child to NULL
        nodes[i]->right = NULL; // Initialize right child to NULL
    }
    
    Node* root = NULL;
    
    // Connect nodes based on parent indices
    for (int i = 0; i < n; i++)
    {
        if (parent_indices[i] == -1)
            // This is the root node
            root = nodes[i];
        else {
            // Connect to its parent
            Node* parent = nodes[parent_indices[i]];
            if (values[i] < parent->key)
                parent->left = nodes[i];
            else
                parent->right = nodes[i];
        }
    }
    
    free(nodes); // Free the array of pointers
    return root;
}

// Function to search for a value in BST
bool search_bst(Node* root, long long target)
{
    if (root == NULL)
        return false;
    
    if (root->key == target)
        return true;
    else if (target < root->key)
        return search_bst(root->left, target);
    else
        return search_bst(root->right, target);
}

// Helper function for inorder traversal to find pairs
void inorder_for_pairs(Node* node, Node* t2, long long target, long long** solutions, int* count)
{
    if (node == NULL)
        return;
    
    // Traverse left subtree
    inorder_for_pairs(node->left, t2, target, solutions, count);
    
    // Process current node
    long long complement = target - node->key; // Calculate the complement value
    // Check if the complement exists in the second tree
    if (search_bst(t2, complement))
    {
        // Check if this pair already exists
        bool exists = false;
        for (int i = 0; i < *count; i++)
            if ((*solutions)[i*2] == node->key && (*solutions)[i*2+1] == complement)
            {
                exists = true;
                break;
            }
        
        if (!exists)
        {
            // Reallocate memory for new solution
            *solutions = (long long*)realloc(*solutions, (*count+1)*2*sizeof(long long));
            (*solutions)[*count*2] = node->key;
            (*solutions)[*count*2+1] = complement;
            (*count)++;
        }
    }
    
    // Traverse right subtree
    inorder_for_pairs(node->right, t2, target, solutions, count);
}

// Function to find all pairs that sum to target
void find_pairs(Node* t1, Node* t2, long long target, long long** solutions, int* solution_count)
{
    *solution_count = 0; // Initialize the solution count to 0
    *solutions = NULL; // Initialize the solutions array to NULL
    inorder_for_pairs(t1, t2, target, solutions, solution_count); // Start the inorder traversal
}

// Comparison function for qsort
int compare_solutions(const void* a, const void* b)
{
    const long long* pair1 = (const long long*)a;
    const long long* pair2 = (const long long*)b;
    
    // Compare the first values
    if (pair1[0] < pair2[0]) return -1;
    if (pair1[0] > pair2[0]) return 1;
    
    // If first values are equal, compare second values
    if (pair1[1] < pair2[1]) return -1;
    if (pair1[1] > pair2[1]) return 1;
    
    return 0;
}

// Function to sort solutions by the first value
void sort_solutions(long long** solutions, int count)
{
    qsort(*solutions, count, 2*sizeof(long long), compare_solutions);
}

// Function to print preorder traversal
void print_preorder(Node* root, int i)
{
    if (root == NULL)
        return;
    
    if (flag_scope[i-1] == 0)
    {
        printf("%lld", root->key);
        flag_scope[i-1] = 1;
    }
    else
        printf(" %lld", root->key);
    
    print_preorder(root->left, i);
    
    print_preorder(root->right, i);
}

// Function to free the tree memory
void free_tree(Node* root)
{
    if (root == NULL)
        return;
    
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}