#include "../includes/priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

PriorityQueuePtr createPriorityQueue(int initialCapacity) {
    // Create a priority queue with a given initial capacity
    PriorityQueuePtr pq = (PriorityQueuePtr)malloc(sizeof(PriorityQueue));
    pq->data = (ElementType *)malloc((initialCapacity + 1) * sizeof(ElementType));
    pq->size = 0;
    pq->capacity = initialCapacity;
    return pq;
}

void destroyPriorityQueue(PriorityQueuePtr pq) {
    // Destroy the priority queue and free memory
    free(pq->data);
    free(pq);
}

void resizePriorityQueue(PriorityQueuePtr pq, int newCapacity) {
    // Resize the priority queue to a new capacity
    pq->data = (ElementType *)realloc(pq->data, (newCapacity + 1) * sizeof(ElementType));
    pq->capacity = newCapacity;
}

bool isEmpty(PriorityQueuePtr pq) {
    // Check if the priority queue is empty
    return pq->size == 0;
}

bool Compare(ElementType a, ElementType b){
    // Compare two elements based on their distance
    return a.dis < b.dis; 
}

void pushBack(PriorityQueuePtr pq, ElementType value) {
    if (pq->size == pq->capacity) {
        // Resize the priority queue if it is full
        resizePriorityQueue(pq, pq->capacity * 2);
    }
    int i = ++pq->size;
    // Insert the new element at the end of the queue
    while ( i > 1 && Compare(value,pq->data[i / 2])) {
        pq->data[i] = pq->data[i / 2];
        i /= 2;
    }
    pq->data[i] = value;
}

ElementType popFront(PriorityQueuePtr pq, int index) {
    int i = index + 1;
    ElementType value = pq->data[i];
    while( i <= pq->size / 2) {
        int child = i * 2;
        // Find the larger child
        if (child < pq->size && Compare(pq->data[child + 1], pq->data[child])) {
            child++;
        }
        // If the current element is larger than the larger child, break
        if (Compare(pq->data[pq->size], pq->data[child])) break;
        pq->data[i] = pq->data[child];
        i = child;
    }
    // Insert the last element at the position of the removed element
    pq->data[i] = pq->data[pq->size]; 
    pq->size--; 
    return value;
}

void printPriorityQueue(PriorityQueuePtr pq) {
    // For Debugging
    for (int i = 1; i <= pq->size; i++) {
        printf("%d ", pq->data[i].v);
    }
    printf("\n");
}

int searchHeap(PriorityQueuePtr pq, int target,int index) {
    // Search for a target element in the heap
    if(index > pq->size || pq->data[index].dis > pq->data[1].dis) {
        return -1; 
    }
    if(pq->data[index].v == target) return index - 1;
    // Recursively search in the left and right subtrees
    int left = searchHeap(pq, target, index * 2);
    if(left != -1) return left;
    int right = searchHeap(pq, target, index * 2 + 1);
    return right;
}

int isHeapTop(PriorityQueuePtr pq, int data){
    // Check if the top element of the priority queue is a heap
    return searchHeap(pq, data, 1);
}