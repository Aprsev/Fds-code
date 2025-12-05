#pragma once
#include "bool.h"

// GraphNode structure
typedef struct GraphNodes{
    int data;
    struct GraphEdges *firstEdge; // pointer to the first edge of the node
} GraphNodes,*GraphNodesPtr;

// GraphEdges structure
// Each edge connects two nodes and has a weight
typedef struct GraphEdges{
    int v;
    int weight;
    struct GraphEdges *next; // pointer to the next edge in the list
} GraphEdges,*GraphEdgesPtr; 

// Graph structure
typedef struct Graph{
    int Nv,Ne; // Nv = number of vertices, Ne = number of edges
    GraphNodes * nodes; // array of nodes
} Graph,*GraphPtr;

GraphPtr createGraph(int n);   // create a graph with n vertices
void destroyGraph(GraphPtr G); // destroy the graph and free memory
void addEdge(GraphPtr G, int u, int v, int weight);  // add an edge to the graph
bool isDijkstraSequence(GraphPtr G, int *seq); // check if the sequence is a Dijkstra sequence