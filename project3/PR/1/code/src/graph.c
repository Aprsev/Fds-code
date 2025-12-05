#include "../includes/graph.h"
#include "../includes/priority_queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

GraphPtr createGraph(int n){
    // Create a graph with n vertices
    GraphPtr G = (GraphPtr)malloc(sizeof(Graph));
    G->Nv = n;
    G->Ne = 0;
    // Allocate memory for the nodes array
    G->nodes = (GraphNodesPtr)malloc(n * sizeof(GraphNodes));
    for(int i = 0; i < n; i++){
        // Initialize each node
        G->nodes[i].data = i+1;
        G->nodes[i].firstEdge = NULL;
    }
    return G;
}

void destroyGraph(GraphPtr G){
    // Destroy the graph and free memory
    for(int i = 0; i < G->Nv; i++){
        GraphEdgesPtr edge = G->nodes[i].firstEdge;
        // Free each edge in the list
        while(edge != NULL){
            GraphEdgesPtr temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    // Free the nodes array
    free(G->nodes);
    free(G);
}

void addEdge(GraphPtr G, int u, int v, int weight){
    // Check if the vertice index are valid
    if(u < 1 || u > G->Nv || v < 1 || v > G->Nv) return;
    GraphEdgesPtr newEdge = (GraphEdgesPtr)malloc(sizeof(GraphEdges));
    // Initialize the new edge
    newEdge->v = v-1;
    newEdge->weight = weight;
    // Chain the new edge to the existing edges of the node
    newEdge->next = G->nodes[u-1].firstEdge;
    G->nodes[u-1].firstEdge = newEdge;
    // Update the number of edges in the graph
    G->Ne++;
}

bool isDijkstraSequence(GraphPtr G, int *seq){
    int *visited = (int *)malloc(G->Nv * sizeof(int));
    int *dist = (int *)malloc(G->Nv * sizeof(int));
    // Initialize visited and dist arrays
    for (int i = 0; i < G->Nv; i++) {
        visited[i] = 0;
        dist[i] = INT32_MAX;
    }
    PriorityQueuePtr pq = createPriorityQueue(G->Nv);
    int cur = 0;
    // Push the first element of the sequence into the priority queue
    pushBack(pq, (Point){0, seq[cur] - 1});
    dist[cur] = 0;
    for(; cur < G->Nv; cur++) {
        // Clear visited elements from the priority queue
        while(!isEmpty(pq) && visited[pq->data[1].v]) popFront(pq, 0);
        // Check if the current element is the top of the priority queue
        int index = isHeapTop(pq, seq[cur] - 1);
        if( index == -1) {
            // If the current element is not the top of the priority queue, free memory and return false
            free(visited);
            free(dist);
            return false;
        }
        Point u = popFront(pq, index);
        if(visited[u.v]) continue;
        visited[u.v] = 1;
        // Get the edges of the current node
        GraphEdgesPtr edge = G->nodes[u.v].firstEdge;
        while(edge != NULL){
            int v = edge->v;
            // Check if the edge is valid and not visited
            if(!visited[v] && dist[u.v] + edge->weight < dist[v]){
                dist[v] = dist[u.v] + edge->weight;
                // Push the new distance and verticle into the priority queue
                pushBack(pq, (Point){dist[v], v});
            }
            edge = edge->next;
        }
    }
    free(visited);
    free(dist);
    return true;
}
