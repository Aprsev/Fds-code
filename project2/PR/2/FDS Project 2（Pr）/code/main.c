#include "bst.h"

int main()
{
    int n1, n2; // Variables to store the number of nodes in T1 and T2
    long long target; // Variable to store the target sum
 
    // Read the number of nodes in T1
    scanf("%d", &n1);
    
    // Allocate memory for T1 values and parent indices
    long long* values1 = (long long*)malloc(n1 * sizeof(long long));
    int* parent_indices1 = (int*)malloc(n1 * sizeof(int));
    
    // Read T1 values and parent indices
    for (int i = 0; i < n1; i++)
        scanf("%lld %d", &values1[i], &parent_indices1[i]);
    
    // Construct T1
    Node* t1 = construct_bst(values1, parent_indices1, n1);
    
    // Read the number of nodes in T2
    scanf("%d", &n2);
    
    // Allocate memory for T2 values and parent indices
    long long* values2 = (long long*)malloc(n2 * sizeof(long long));
    int* parent_indices2 = (int*)malloc(n2 * sizeof(int));
    
    // Read T2 values and parent indices
    for (int i = 0; i < n2; i++)
        scanf("%lld %d", &values2[i], &parent_indices2[i]);
    
    // Construct T2
    Node* t2 = construct_bst(values2, parent_indices2, n2);
    
    // Read the target sum
    scanf("%lld", &target);
    
    // Find all pairs that sum to target
    long long* solutions = NULL; // Pointer to store the array of solutions
    int solution_count = 0; // Variable to store the number of solutions found
    find_pairs(t1, t2, target, &solutions, &solution_count);
    
    // Sort the solutions by the first value in each pair
    sort_solutions(&solutions, solution_count);
    
    // Print results
    if (solution_count > 0)
    {
        printf("true\n");
        // Output all unique solutions
        for (int i = 0; i < solution_count; i++)
            printf("%lld = %lld + %lld\n", target, solutions[i*2], solutions[i*2+1]);
    }
    else
        printf("false\n");
    
    // Print preorder traversal of T1
    print_preorder(t1, 1);
    printf("\n");
    
    // Print preorder traversal of T2
    print_preorder(t2, 2);
    printf("\n");
    
    // Free memory
    free(values1);
    free(parent_indices1);
    free(values2);
    free(parent_indices2);
    free(solutions);
    free_tree(t1);
    free_tree(t2);
    
    return 0;
}