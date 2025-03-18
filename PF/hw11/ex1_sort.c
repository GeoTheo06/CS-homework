/* file: ex1_sort.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Dec 19 2024 */
/* version: 1.0 */

/* Description: This program calculates the number of unique triplets (a,b,c) such that a+b+c=s, where a, b, and c are taken from three respective arrays. */

#include <stdio.h>
#include <stdlib.h>
int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

int binary_search(int *arr, int n, int val) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == val) {
            return 1;
        } else if (arr[mid] < val) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

int main(void) {
    int s;
    scanf("%d", &s);

    // Read first array
    int n1;
    scanf("%d:", &n1);
    int *A = (int *)malloc(n1 * sizeof(int));
    for (int i = 0; i < n1; i++) {
        scanf("%d", &A[i]);
    }

    // Read second array
    int n2;
    scanf("%d:", &n2);
    int *B = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n2; i++) {
        scanf("%d", &B[i]);
    }

    // Read third array
    int n3;
    scanf("%d:", &n3);
    int *C = (int *)malloc(n3 * sizeof(int));
    for (int i = 0; i < n3; i++) {
        scanf("%d", &C[i]);
    }

    // Sort the arrays
    qsort(A, n1, sizeof(int), compare_ints);
    qsort(B, n2, sizeof(int), compare_ints);
    qsort(C, n3, sizeof(int), compare_ints);

    int count = 0;
    for (int i = 0; i < n1; i++) {
        // Skip duplicates in A
        if (i > 0 && A[i] == A[i - 1]) {
            continue;
        }

        for (int j = 0; j < n2; j++) {
            // Skip duplicates in B
            if (j > 0 && B[j] == B[j - 1]) {
                continue;
            }

            int needed = s - A[i] - B[j];
            // Binary search in C
            if (binary_search(C, n3, needed)) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    free(A);
    free(B);
    free(C);

    return 0;
}