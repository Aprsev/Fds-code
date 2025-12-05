#pragma once
#include "bool.h"
#define TEMPLATE(T) typedef T ElementType; \
                    typedef T * ElementTypePtr;   

// Point structure
typedef struct Point{
    int dis, v; // dis = distance, v = vertex
} Point;

TEMPLATE(Point)

typedef struct PriorityQueue{
    ElementTypePtr data; // Array to store the elements of the priority queue
    int size;  // Current number of elements in the priority queue
    int capacity; // Maximum capacity of the priority queue
}PriorityQueue, *PriorityQueuePtr;

PriorityQueuePtr createPriorityQueue(int capacity); // Create a priority queue with a given capacity
void destroyPriorityQueue(PriorityQueuePtr pq); // Destroy the priority queue and free memory
void resizePriorityQueue(PriorityQueuePtr pq, int newCapacity); // Resize the priority queue to a new capacity
void pushBack(PriorityQueuePtr pq, ElementType value); // Add an element to the priority queue
ElementType popFront(PriorityQueuePtr pq, int index); // Remove and return the given index element of the priority queue
bool isEmpty(PriorityQueuePtr pq); // Check if the priority queue is empty
void printPriorityQueue(PriorityQueuePtr pq); // Print the elements of the priority queue
bool Compare(ElementType a, ElementType b); // Compare two elements
int isHeapTop(PriorityQueuePtr pq, int data); // Check if the top element of the priority queue is a heap