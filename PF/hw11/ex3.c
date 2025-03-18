/* file: ex3.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Dec 19 2024 */
/* version: 1.0 */

/* Description: creates a binary tree from a sorted array of integers. A recursive function prints the binary tree in a structured format, dividing nodes into subtrees. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int cmp_int3(const void *x, const void *y) {
    int a = *(int *)x, b = *(int *)y;
    if (a < b) {
        return -1;
    } else {
        return a > b;
    }
}

void printTree(int *arr, int start, int end) {
    int length = end - start + 1;
    if (length == 1) {
        printf("Leaf %d", arr[start]);
        return;
    }
    // Find the middle for root
    int mid = start + (length / 2);
    printf("Tree (");
    printTree(arr, start, mid - 1);
    printf(") %d (", arr[mid]);
    printTree(arr, mid + 1, end);
    printf(")");
}

int main() {
    int n;
    scanf("%d", &n);
    int nodes = (1 << n) - 1;
    int *arr = (int *)malloc(sizeof(int) * nodes);
    for (int i = 0; i < nodes; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, nodes, sizeof(int), cmp_int3);
    printTree(arr, 0, nodes - 1);
    printf("\n");
    free(arr);
    return 0;
}
