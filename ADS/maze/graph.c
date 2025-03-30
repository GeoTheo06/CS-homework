#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Initialize a node that represents a neighbour.
ListPointer createNode(int nodeIndex, int weight)
{
    ListPointer newNode = (ListPointer)malloc(sizeof(ListNode));
    newNode->vertex = nodeIndex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Adds a node to the graph neighbourList, where each entry is a linked list.
void addEdge(ListPointer *neighbourList, int src, int dest, int weight)
{
    // Create a new node for dest.
    ListPointer newNode = createNode(dest, weight);

    // Insert at current head of list.
    newNode->next = neighbourList[src];
    neighbourList[src] = newNode;
}