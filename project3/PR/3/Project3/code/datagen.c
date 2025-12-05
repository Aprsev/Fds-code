#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static int graph[1001][1001];//adajacency matrix

// Function to generate 100 permutations of 1000 vertices
void permutation(FILE *fp, int n, int k) {
    int v[1001];
    for (int i = 1; i <= n; i++) {
        v[i] = i;
    }

    for (int seq = 0; seq < k; seq++) {
        // Shuffle the array to generate a random permutation
        for (int i = n; i > 1; i--) {
            int j = rand() % i + 1; // Random index between 1 and i
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }

        for (int i = 1; i <= n; i++) { // Write the permutation to the file
            fprintf(fp, "%d ", v[i]);
        }
        fprintf(fp, "\n");
    }
}

int main()
{
    FILE *fp;
    fp = fopen("case2.txt", "w+");//open file to write
    srand((unsigned)time(NULL));

    // Create a graph which is guaranteed to be connected, 999 edges used
    for (int i = 1; i <= 999; i++) {
        graph[i][i + 1] = graph[i+1][i] = rand() % 100 + 1; // Set weight to 1-100
    }

    int cnt = 999; // Variable to count edges
    for (; cnt < 100000;) // Set 100000 edges
    {
        int m = rand() % 1000 + 1; // Row
        int n = rand() % 1000 + 1; // Column
        if ((n != m) && (graph[m][n] == 0))
        {
            graph[m][n] = graph[n][m] = rand() % 100 + 1; // Set edges
            cnt++;
        }
    }

    fprintf(fp, "%d %d\n", 1000, 100000); // Print the number of vertices and edges
    for (int i = 1; i <= 1000; i++) {
        for (int j = i; j <= 1000; j++) {
            if (graph[i][j] != 0) {
                fprintf(fp, "%d %d %d\n", i, j, graph[i][j]); // Print the edges
            }
        }
    }
    fprintf(fp, "%d\n", 100);

    // Generate 100 random permutations of 1000 vertices
    permutation(fp, 1000, 100);

    fclose(fp);
    return 0;
}