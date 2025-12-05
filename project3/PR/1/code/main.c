#include <stdio.h>
#include "includes/graph.h"
#include <stdlib.h>

int main(){
    int nv,ne;
    scanf("%d %d",&nv,&ne);
    // Create a graph with nv vertices
    GraphPtr g = createGraph(nv);
    for(int i = 0; i < ne; i++){
        int u,v,weight;
        scanf("%d %d %d",&u,&v,&weight);
        // Undirected graph: add edges in both directions
        addEdge(g,u,v,weight);
        addEdge(g,v,u,weight);
    }
    int cases;
    scanf("%d",&cases);
    int *seq = (int*)malloc(nv * sizeof(int)); 
    for (int i = 0; i < cases; i++){
        // Read the sequence of vertices
        for(int j = 0;j < nv;j++){
            scanf("%d",&seq[j]);
        }
        // Check if the sequence is a Dijkstra sequence
        bool res = isDijkstraSequence(g,seq);
        if (res == true)
            // If the sequence is a Dijkstra sequence, print "YES"
            puts("YES");
        else puts("NO");
    }
    // Free the allocated memory
    destroyGraph(g);
    return 0;
}