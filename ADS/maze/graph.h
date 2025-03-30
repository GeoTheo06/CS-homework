#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

// Neighbours of a vertex are kept as linked lists.
typedef struct ListNode
{
    int vertex;
    int weight;
    struct ListNode *next;
} ListNode;

typedef ListNode *ListPointer;

ListPointer createNode(int nodeIndex, int weight);

void addEdge(ListPointer *neighbourList, int src, int dest, int weight);

void printGraph(ListPointer *neighbourList, int nodes);

#endif