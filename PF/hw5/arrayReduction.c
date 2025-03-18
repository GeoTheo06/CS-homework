/* file: arrayReduction.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Oct 08 2024 */
/* version: 1.0 */

/* Description: This program inputs an array of numbers and outputs how many numbers are left after we subtract the ones that are equal to the sum of the remaining elements*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char col;
    scanf("%c", &col);  // read the :
    int temp;
    int *arr = (int *)malloc(sizeof(int));
    for (int i = 0; i < n; i++) {
        arr = (int *)realloc(arr, sizeof(int) * (i + 1));
        scanf("%d", &arr[i]);
    }
    int reduce = 1;
    while (reduce) {
        // find the max element in the array
        int max = -1, maxPos;
        for (int i = 0; i < n; i++) {
            if (arr[i] > max) {
                max = arr[i];
                maxPos = i;
            }
        }

        // calculate the sum of all elements except max
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (i != maxPos && arr[i] != -1) {
                sum += arr[i];
            }
        }

        if (sum == max) {
            arr[maxPos] = -1;
        } else {
            reduce = 0;
        }
    }

    // calculate how many elements exist in the array
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != -1) {
            count++;
        }
    }
    printf("%d\n", count);
}