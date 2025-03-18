/* file: splitter.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Oct 16 2024 */
/* version: 1.0 */

/* Description:
 * This program reads a sequence of letters and prints the next permutaiton in lexicographic order
 */

#include <stdio.h>
#include <stdlib.h>

void swap(char *xp, char *yp) {
    char temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main(int argc, char *argv[]) {
    // read input
    char ch;
    int size = 2, n = 0;
    char *arr = (char *)malloc(sizeof(char) * size);
    scanf("%c", &ch);
    while (ch != '.') {
        if (size == n + 1) {
            size *= 2;
            arr = (char *)realloc(arr, sizeof(char) * size);
        }
        arr[n] = ch;
        n++;
        scanf("%c", &ch);
    }
    arr[n] = '\0';  // Null-terminate the string

    // Find the pivot
    int count = n - 1;
    while (count > 0 && arr[count - 1] >= arr[count]) {
        count--;
    }
    int pivot = count - 1;

    if (pivot >= 0) {
        // Find the next bigger element after the pivot
        int max = pivot + 1;
        for (int i = pivot + 2; i < n; i++) {
            if (arr[i] > arr[pivot] && arr[i] <= arr[max]) {
                max = i;
            }
        }

        // Swap the max and the pivot
        if (max != -1) {
            char temp = arr[max];
            arr[max] = arr[pivot];
            arr[pivot] = temp;
        }

        // Reverse the suffix starting at pivot + 1
        int start = pivot + 1;
        int end = n - 1;
        while (start < end) {
            swap(&arr[start], &arr[end]);
            start++;
            end--;
        }
    }

    printf("%s\n", arr);

    free(arr);  // Free the allocated memory
    return 0;
}
