/* file: ex4_complement.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Jan 09 2024 */
/* version: 1.0 */

/* Description: This program reads a series of closed intervals, merges overlapping intervals, and computes the complement of these intervals. */

#include <stdio.h>
#include <stdlib.h>

int *copySubArray(int left, int right, int arr[]) {
    int *copy = malloc((right - left) * sizeof(int));
    for (int i = left; i < right; i++) {
        copy[i - left] = arr[i];
    }
    return copy;
}

void mergeSort(int length, int arr[], int end[]) {
    if (length <= 1) {
        return;
    }

    int mid = length / 2;
    int *left = copySubArray(0, mid, arr);
    int *right = copySubArray(mid, length, arr);
    int *left2 = copySubArray(0, mid, end);
    int *right2 = copySubArray(mid, length, end);

    mergeSort(mid, left, left2);
    mergeSort(length - mid, right, right2);

    int idx = 0;
    int l = 0;
    int r = 0;
    while ((l < mid) && (r < length - mid)) {
        if (left[l] < right[r]) {
            arr[idx] = left[l];
            end[idx] = left2[l];
            l++;
        } else {
            arr[idx] = right[r];
            end[idx] = right2[r];
            r++;
        }
        idx++;
    }
    while (l < mid) {
        arr[idx] = left[l];
        end[idx] = left2[l];
        idx++;
        l++;
    }
    while (r < length - mid) {
        arr[idx] = right[r];
        end[idx] = right2[r];
        idx++;
        r++;
    }
    free(left);
    free(left2);
    free(right);
    free(right2);
}

int main() {
    int n;
    scanf("%d", &n);
    int *start = (int *)malloc(sizeof(int) * n);
    int *end = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n * 2; i++) {
        if (i % 2 == 0) {
            scanf("%d", &start[i / 2]);
        } else {
            scanf("%d", &end[(i - 1) / 2]);
        }
    }

    mergeSort(n, start, end);
    // for (int i = 0; i < n; i++) {
    //     printf("%d, %d\n", start[i], end[i]);
    // }

    // fix overlaps
    for (int i = 1; i < n; i++) {
        if (end[i - 1] > start[i]) {
            start[i] = end[i - 1];
        }
        if (start[i] > end[i]) {
            end[i] = start[i];
        }
    }
    int beginning = 1;
    for (int i = 0; i < n * 2; i++) {
        if (i % 2 == 0) {
            if (beginning < start[i / 2]) {
                printf("[%d,%d],", beginning, start[i / 2] - 1);
            }
        } else {
            int index = (i - 1) / 2;
            beginning = end[index] + 1;
        }
    }

    printf("[%d,INFINITY]\n", end[n - 1] + 1);

    free(start);
    free(end);
    return 0;
}