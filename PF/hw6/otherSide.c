/* file: splitter.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Oct 16 2024 */
/* version: 1.0 */

/* Description:
 * this program reads a matrix and finds the shortest path from the left of it to the right.
 */
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    int min = a;
    if (b < min) {
        min = b;
    }
    return min;
}

int main() {
    int r, c;
    scanf("%d %d", &r, &c);
    int **arr = (int **)malloc(sizeof(int *) * r);
    int **dp = (int **)malloc(sizeof(int *) * r);

    // allocate 2d array memory
    for (int i = 0; i < r; i++) {
        arr[i] = (int *)malloc(sizeof(int) * c);
        dp[i] = (int *)malloc(sizeof(int) * c);
    }

    // read input
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    int minRes;
    if (r > 1) {
        // initialize the algorithm (dp has to have one column because it can't be compared with the previous one as it doesn't exist)
        for (int i = 0; i < r; i++) {
            dp[i][0] = arr[i][0];
        }

        for (int j = 1; j < c; j++) {
            for (int i = 0; i < r; i++) {
                if (i == 0) {  // if we are on first row
                    dp[i][j] = arr[i][j] + min(dp[i][j - 1], dp[i + 1][j - 1]);
                } else if (i == r - 1) {  // if we are on last row
                    dp[i][j] = arr[i][j] + min(dp[i][j - 1], dp[i - 1][j - 1]);
                } else {  // if we are in the middle
                    dp[i][j] = arr[i][j] + min(min(dp[i + 1][j - 1], dp[i - 1][j - 1]), dp[i][j - 1]);
                }
            }
        }
        // find the minimum sum
        minRes = dp[0][c - 1];
        for (int i = 1; i < r; i++) {
            if (dp[i][c - 1] < minRes) {
                minRes = dp[i][c - 1];
            }
        }
    } else {  // have to calculate for the case that c=1 seperately because my algorithm doesn't cover it

        minRes = arr[0][0];
        for (int i = 1; i < c; i++) {
            // printf("%d", arr[0][i]);
            if (arr[0][i] < minRes) {
                minRes = arr[0][i];
            }
        }
    }

    printf("%d\n", minRes);
    return 0;
}
