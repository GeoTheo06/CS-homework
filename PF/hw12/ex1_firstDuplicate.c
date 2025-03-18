/* file: ex1_firstDuplicate.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Jan 09 2024 */
/* version: 1.0 */

/* Description: This program finds the first integer in an array that has at least one duplicate and prints its value along with all its indices. If no duplicates are found, it outputs "NOT FOUND"*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int *count = (int *)malloc(sizeof(int) * 1000001);

    for (int i = 0; i < 1000001; i++) {
        count[i] = 0;
    }

    int *idcs = (int *)malloc(sizeof(int) * 1000001);
    int isNum = 0;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        if (count[num] == 0) {
            idcs[num] = i;
        }

        if (count[num] == 1) {
            isNum = 1;
        }
        count[num]++;
    }
    if (!isNum) {
        printf("NOT FOUND\n");
        free(count);
        free(arr);
        free(idcs);
        return 0;
    }

    int minIdx = 1000001;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        if (count[num] >= 2 && idcs[num] < minIdx) {
            minIdx = idcs[num];
        }
    }
    int minNum = arr[minIdx];

    printf("%d: ", minNum);
    int firstNumDone = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == minNum) {
            if (firstNumDone) {
                printf(",");
            }
            printf("%d", i);
            firstNumDone = 1;
        }
    }

    printf("\n");
    free(count);
    free(arr);
    free(idcs);

    return 0;
}