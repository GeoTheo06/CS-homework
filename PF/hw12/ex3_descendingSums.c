/* file: ex3_descendingSums.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Jan 09 2024 */
/* version: 1.0 */

/* Description: This program generates all possible descending partitions of an integer n and prints them in descending order as sums of integers. */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[51];

    for (int i = 0; i <= 50; i++) {
        arr[i] = 0;
    }

    arr[0] = n;
    printf("%d\n", arr[0]);

    int index = 0;
    int temp;
    int countOnes = 0;
    int numBeforeOne = 0;
    while (countOnes < index + 1) {
        countOnes = 0;

        // counts ones and makes 0 the places with 1s.
        for (int i = 0; i <= index; i++) {
            if (arr[i] == 1) {
                countOnes++;
                arr[i] = 0;
            }
        }

        numBeforeOne = index - countOnes;

        arr[numBeforeOne]--;

        int numbersThatNeedPutting = countOnes + 1;
        temp = numBeforeOne + 1;
        while (numbersThatNeedPutting >= arr[numBeforeOne]) {
            arr[temp] = arr[numBeforeOne];
            numbersThatNeedPutting -= arr[numBeforeOne];
            temp++;
        }
        // in the end put whatever's left.
        arr[temp] = numbersThatNeedPutting;

        temp = 0;
        countOnes = 0;
        while (temp <= 50 && arr[temp] != 0) {
            if (temp != 0) {
                printf("+");
            }
            printf("%d", arr[temp]);

            if (arr[temp] == 1) {
                countOnes++;
            }

            temp++;
        }
        index = temp - 1;
        printf("\n");
    }

    return 0;
}