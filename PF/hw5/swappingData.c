/* file: swappingData.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Oct 08 2024 */
/* version: 1.0 */

/* Description: This program reads an array and some pairs of the indexes of the array and swaps the elements of each pair. Then outputs YES or NO indicating whether or not the modified array is in ascending order*/

#include <stdio.h>
#include <stdlib.h>

// swaps 2 elements in the array and returns the modified array
int *swap(int *arr, int i1, int i2) {
    int temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
    return arr;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);

    // reads the array
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // does the modifications
    int i1, i2;
    scanf("%d %d", &i1, &i2);
    while (i1 != 0 || i2 != 0) {
        arr = swap(arr, i1, i2);
        scanf("%d %d", &i1, &i2);
    }

    // checks if it is in ascending order or not
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}