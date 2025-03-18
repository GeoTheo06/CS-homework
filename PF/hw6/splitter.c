/* file: splitter.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Oct 16 2024 */
/* version: 1.0 */

/* Description:
 * This program reads a series of numbers and outputs the number that all total number of numbers lower than it is equal to the total number of numbers bigger than it.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int temp;
    int n = 0;
    int *arr = (int *)malloc(sizeof(int) * 2);
    int size = 2;
    scanf("%d", &temp);

    // read input
    while (temp != 0) {
        if (size == n + 1) {
            size *= 2;
            arr = (int *)realloc(arr, sizeof(int) * size);
        }
        arr[n] = temp;
        n++;
        scanf("%d", &temp);
    }

    // i will store all numbers that have not been visited so that i don't go over the same numbers again and again
    char visited[100];
    for (int i = 0; i < 100; i++) {
        visited[i] = '0';
    }

    int smallerSum = -1, biggerSum = -2;  // initializing them with different values for the check in the first loop
    int middle = arr[0];
    // will run 100 times max because i check if they are visited first
    for (int i = 0; i < n && smallerSum != biggerSum; i++) {
        if (visited[i] == '0') {
            smallerSum = 0;
            biggerSum = 0;
            middle = arr[i];
            for (int k = 0; k < n; k++) {
                if (arr[k] < middle) {
                    smallerSum++;
                } else if (arr[k] > middle) {
                    biggerSum++;
                }
            }

            visited[i] = '1';
        }
    }
    if (smallerSum == biggerSum) {
        printf("%d\n", middle);
    } else {
        printf("UNBALANCED\n");
    }

    free(arr);
    return 0;
}
