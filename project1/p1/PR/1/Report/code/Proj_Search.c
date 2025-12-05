#include <stdio.h>
#include <time.h>

clock_t start, stop;  // Variables to store the start and stop times
double duration;  // Stores the execution time

// Function prototypes
int BinaSearch_Circulation(int a[], int left, int right, int x);
int BinaSearch_Recursion(int a[], int left, int right, int x);
int SequeSearch_Circulation(int a[], int n, int x);
int SequeSearch_Recursion(int a[], int n, int x);

int main() {
    int n = 0, x = 0;
    int k = 1000000, status = -1;  // k is the number of test iterations

    // Read the input values: array size (n), target value (x), and the number of iterations (k)
    scanf("%d %d %d", &n, &x, &k);  
    int a[n];  // Declare an array of size n

    // Initialize the array with sequential values (0, 1, 2, ..., n-1)
    for (int i = 1; i < n; i++) {
        a[i] = i;
    }

    printf("Circulation Times k = %d\n", k);

    // Binary Search using Recursion
    printf("Binary Search by Recursion:\n");
    start = clock();  // Record start time
    for (int i = 0; i < k; i++) {
        status = BinaSearch_Recursion(a, 0, n, x);
    }
    stop = clock();  // Record stop time
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Time is %f\n stop = %ld, start = %ld, delta = %ld\n\n", duration, stop, start, stop - start);

    // Sequential Search using Recursion
    printf("Sequence Search by Recursion:\n");
    start = clock();
    for (int i = 0; i < k; i++) {
        status = SequeSearch_Recursion(a, n, x);
    }
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Time is %f\n stop = %ld, start = %ld, delta = %ld\n\n", duration, stop, start, stop - start);

    // Binary Search using Iteration
    printf("Binary Search by Circulation:\n");
    start = clock();
    for (int i = 0; i < k; i++) {
        status = BinaSearch_Circulation(a, 0, n, x);
    }
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Time is %f\n stop = %ld, start = %ld, delta = %ld\n\n", duration, stop, start, stop - start);

    // Sequential Search using Iteration
    printf("Sequence Search by Circulation:\n");
    start = clock();
    for (int i = 0; i < k; i++) {
        status = SequeSearch_Circulation(a, n, x);
    }
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Time is %f\n stop = %ld, start = %ld, delta = %ld\n\n", duration, stop, start, stop - start);

    // Final result check
    if (status == 1) {
        printf("Find!\n");  // If status is 1, the target was found
    } else if (status == 0) {
        printf("Not Find!\n");  // If status is 0, the target was not found
    } else {
        printf("ERROR!\n");  // If status is neither 1 nor 0, there is an error
    }

    return 0;
}

// Iterative Binary Search (Loop-Based)
int BinaSearch_Circulation(int a[], int left, int right, int x) {
    int mid;
    while (left < right) {  // Continue searching while left is less than right
        mid = (left + right) / 2;  // Find the middle index
        if (a[mid] > x) {
            right = mid - 1;  // Search in the left half
        } else if (a[mid] < x) {
            left = mid + 1;  // Search in the right half
        } else {
            return 1;  // Target found
        }
    }
    return 0;  // Target not found
}

// Recursive Binary Search
int BinaSearch_Recursion(int a[], int left, int right, int x) {
    int mid = (left + right) / 2;  // Calculate the middle index
    if (left > right) {  // Base case: search range is invalid
        return 0;  // Target not found
    }
    if (a[mid] == x) {
        return 1;  // Target found
    } else if (a[mid] < x) {
        return BinaSearch_Recursion(a, mid + 1, right, x);  // Search in the right half
    } else {
        return BinaSearch_Recursion(a, left, mid - 1, x);  // Search in the left half
    }
}

// Iterative Sequential Search (Loop-Based)
int SequeSearch_Circulation(int a[], int n, int x) {
    for (int i = 0; i < n; i++) {  // Traverse the entire array
        if (x == a[i]) {  // If the current element matches the target
            return 1;  // Target found
        }
    }
    return 0;  // Target not found
}

// Recursive Sequential Search

int SequeSearch_Recursion(int a[], int n, int x){
    if(n == 0){ // Base case: if only one element left
        return 0;
    }
    if(a[n-1] == x){// Check if the  element matches the target
        return 1;
    }
    return SequeSearch_Recursion(a, n-1, x); // Recursively check remaining elements

}
