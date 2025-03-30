#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

// Node in dijkstra's priority queue.
typedef struct HeapNode
{
    int vertex;
    int distance;
    int state; // Whether the node is in the reversed maze.
} HeapNode;

typedef struct
{
    HeapNode **data; // Actual MinHeap.
    int *pos;        // Stores the position of the vertex in data.
    int size;
} MinHeap;

// Creates and initializes a node of the heap.
HeapNode *createHeapNode(int vertex, int weight, int state)
{
    HeapNode *newNode = malloc(sizeof(HeapNode));
    newNode->vertex = vertex;
    newNode->distance = weight;
    newNode->state = state;
    return newNode;
}

// Allocates memory for a Minheap and returns it.
MinHeap *createMinHeap(int nodes)
{
    MinHeap *pq = (MinHeap *)malloc(sizeof(MinHeap));
    pq->data = malloc(sizeof(HeapNode *) * nodes);
    pq->pos = calloc(nodes, sizeof(int));
    
    pq->size = 0;
    return pq;
}

// Swap 2 integers.
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Moves an element at index 'idx' up in the heap.
void heapifyUp(MinHeap *pq, int idx)
{
    while (idx > 0)
    {
        int parent = (idx - 1) / 2;
        // If current element is smaller than its parent, swap the nodes in the heap array.
        if (pq->data[idx]->distance < pq->data[parent]->distance)
        {
            HeapNode *temp = pq->data[idx];
            pq->data[idx] = pq->data[parent];
            pq->data[parent] = temp;

            // Also swap the elements in the pos array.
            swap(&pq->pos[2 * pq->data[idx]->vertex + pq->data[idx]->state],
                 &pq->pos[2 * pq->data[parent]->vertex + pq->data[parent]->state]);

            idx = parent;
        }
        else
        {
            break;
        }
    }
}

// Moves an element at index 'idx' down to restore the MinHeap.
void heapifyDown(MinHeap *pq, int idx)
{
    while (1)
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < pq->size && pq->data[left]->distance < pq->data[smallest]->distance)
        {
            smallest = left;
        }
        if (right < pq->size && pq->data[right]->distance < pq->data[smallest]->distance)
        {
            smallest = right;
        }

        if (smallest != idx)
        {
            // Swap the nodes in the heap array.
            HeapNode *temp = pq->data[idx];
            pq->data[idx] = pq->data[smallest];
            pq->data[smallest] = temp;

            // Update positions: the vertices have swapped indices.
            swap(&pq->pos[2 * pq->data[idx]->vertex + pq->data[idx]->state],
                 &pq->pos[2 * pq->data[smallest]->vertex + pq->data[smallest]->state]);

            // Continue heapifying down from the new index.
            idx = smallest;
        }
        else
        {
            break;
        }
    }
}

// Removes the smallest (root) element from the priority queue and returns it.
HeapNode *popMinHeap(MinHeap *pq)
{
    if (pq->size == 1)
    {
        HeapNode *node = pq->data[0];
        pq->data[0] = NULL; // Clear the pointer to avoid duplicate free.
        pq->size--;
        return node;
    }
    HeapNode *rootNode = pq->data[0];
    HeapNode *lastNode = pq->data[pq->size - 1];

    // Move the last element to the root and clear the old index.
    pq->data[0] = lastNode;
    pq->data[pq->size - 1] = NULL; // Clear duplicate reference.
    pq->size--;

    pq->pos[lastNode->vertex * 2 + lastNode->state] = 0;
    pq->pos[rootNode->vertex * 2 + rootNode->state] = -1;

    // Heapify downward to restore the MinHeap property.
    heapifyDown(pq, 0);
    return rootNode;
}

int isEmpty(MinHeap *pq)
{
    return pq->size == 0;
}

// Free the priority queue's variables.
void destroyMinHeap(MinHeap *pq, int nodes)
{
    if (pq)
    {
        // free the data array
        for (int i = 0; i < nodes; i++)
        {
            if (pq->pos[i] != -1)
            {
                free(pq->data[i]);
            }
        }
        free(pq->data);
        free(pq->pos);
        free(pq);
    }
}

void dijkstra(ListPointer *originalNeighbourList, ListPointer *reverseNeighbourList, int nodes, int *cButtons)
{
    // Helps build the best path.
    int *previous = malloc(nodes * 2 * sizeof(int));

    // Prevents from accessing deleted memory.
    int *distances = malloc(nodes * 2 * sizeof(int));

    MinHeap *minHeap = createMinHeap(nodes * 2);
    minHeap->size = 2 * nodes;

    // Initialization step.
    int id;
    for (int v = 0; v < nodes; v++)
    {
        for (int s = 0; s < 2; s++)
        {
            // Each vertex can be reversed, s(tate) keeps this change.
            id = 2 * v + s;

            if (v == 0 && s == 0)
            {
                distances[id] = 0;
            }
            else
            {
                distances[id] = INT_MAX;
            }
            minHeap->data[id] = createHeapNode(v, distances[id], s);
            minHeap->pos[id] = id;

            // No chamber has yet been visited.
            previous[id] = -1;
        }
    }

    while (!isEmpty(minHeap))
    {
        HeapNode *node = popMinHeap(minHeap);
        int u = node->vertex;
        int s = node->state;
        // Unique id determined by vertex and state.
        int id = 2 * u + s;

        // Press the button if possible, relaxing distance to button press to 0.
        if (cButtons[u])
        {
            int idToggle = 2 * u + (1 - s);
            if (distances[id] < distances[idToggle])
            {
                distances[idToggle] = distances[id];
                previous[idToggle] = id;
                minHeap->data[minHeap->pos[idToggle]]->distance = distances[idToggle];
                // After relaxing, restore the heap.
                heapifyUp(minHeap, minHeap->pos[idToggle]);
            }
        }
        // Current neighbours depend on state of maze.
        ListPointer *activeGraph = (s == 0) ? originalNeighbourList : reverseNeighbourList;

        // Traverse through the neighbours, relaxation step.
        for (ListNode *i = activeGraph[u]; i != NULL; i = i->next)
        {
            int v = i->vertex;
            // The state remains the same on travel
            int neighbourId = 2 * v + s; 
            if (distances[id] != INT_MAX && distances[id] + i->weight < distances[neighbourId])
            {
                distances[neighbourId] = distances[id] + i->weight;
                previous[neighbourId] = id;
                minHeap->data[minHeap->pos[neighbourId]]->distance = distances[neighbourId];
                // After relaxing, restore the heap.
                heapifyUp(minHeap, minHeap->pos[neighbourId]);
            }
        }
        free(node);
    }

    // Determine the best distance at the destination, whether reversed or original maze.
    int id0 = (nodes - 1) * 2 + 0, id1 = nodes * 2 - 1;
    int bestDist = distances[id0];
    int bestState = 0;
    if (distances[id1] < bestDist)
    {
        bestDist = distances[id1];
        bestState = 1;
    }
    if (bestDist == INT_MAX)
    {
        printf("IMPOSSIBLE\n");

        free(previous);
        free(distances);
        destroyMinHeap(minHeap, nodes * 2);

        return;
    }
    printf("%d\n", bestDist);

    // Reconstruct path from (0,0) to (n-1, bestState)
    int *path = malloc(nodes * 2 * sizeof(int)), pathLen = 0;
    int current = (nodes - 1) * 2 + bestState;
    // Construct the path in reverse.
    while (current != -1)
    {
        path[pathLen] = current;
        pathLen++;
        current = previous[current];
    }
    // Print the path in order (convert to 1-based indexing).
    // Mark where a button was pressed (i.e. when state changes between consecutive nodes).
    int lastPrinted = -1;
    for (int i = pathLen - 1; i >= 0; i--)
    {
        int vertex = path[i] / 2;
        int state = path[i] % 2;

        // Avoid printing a button press as a step in the path by skipping iteration.
        if (vertex == lastPrinted)
        {
            continue;
        }
        else
        {
            printf("%d", vertex + 1);
        }
        if (i > 0)
        {
            int prevState = path[i - 1] % 2;
            // If state changed, that means a button press occurred at this chamber.
            if (state != prevState)
            {
                printf(" R");
            }
        }
        printf("\n");
        lastPrinted = vertex;
    }
    free(previous);
    free(distances);
    free(path);
    destroyMinHeap(minHeap, nodes * 2);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    // Arrays of lists, entry i contains all neighbors of node i.
    ListPointer *originalNeighbourList = malloc(n * sizeof(ListPointer));
    ListPointer *reverseNeighbourList = malloc(n * sizeof(ListPointer));

    // Initialize original graph and reversed graph.
    for (int i = 0; i < n; i++)
    {
        originalNeighbourList[i] = NULL;
        reverseNeighbourList[i] = NULL;
    }

    int *cButtons = calloc(n, sizeof(int));

    // Read the input.
    int temp;
    scanf("%d", &temp);
    while (temp != -1)
    {
        cButtons[temp - 1] = 1;
        scanf("%d", &temp);
    }

    int src, dst, weight;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &src, &dst, &weight);
        // Vertices are stored in base 0 in the data structures.
        addEdge(originalNeighbourList, src - 1, dst - 1, weight);
        addEdge(reverseNeighbourList, dst - 1, src - 1, weight);
    }

    dijkstra(originalNeighbourList, reverseNeighbourList, n, cButtons);

    // Free the dynamically allocated variables.
    free(cButtons);

    for (int i = 0; i < n; i++)
    {
        ListPointer current = originalNeighbourList[i];
        while (current)
        {
            ListPointer temp = current;
            current = current->next;
            free(temp);
        }
        current = reverseNeighbourList[i];
        while (current)
        {
            ListPointer temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(originalNeighbourList);
    free(reverseNeighbourList);

    return 0;
}
