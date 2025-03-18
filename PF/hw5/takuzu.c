/* file: takuzu.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Oct 08 2024 */
/* version: 1.0 */

/* Description: Reads the solution of a takuzu game, stores it in a 2d array and checks if the solution is valid based on the criteria: There is an equal number of 1s and 0s in each row and column (hence four 0s and four 1s) and no more than two of either number adjacent to each other. Moreover, there can be no identical rows, nor can there be identical columns*/

#include <stdio.h>
#include <stdlib.h>

int checkCriteria(int grid[8][8]) {
    // check if there are 4 0s and 4 1s horizontally and vertically
    for (int i = 0; i < 8; i++) {
        int counterH = 0;
        int counterV = 0;
        for (int j = 0; j < 8; j++) {
            // counting horizontal
            if (grid[i][j] == 0) {
                counterH++;
            }
            // counting vertical
            if (grid[j][i] == 0) {
                counterV++;
            }
        }
        if (counterV != 4 || counterH != 4) {
            return 0;
        }
    }

    // check if there are 3 0s or 1s next to each other horizontally and vertically
    for (int i = 0; i < 8; i++) {
        int counterH0 = 0;
        int counterH1 = 0;
        int counterV0 = 0;
        int counterV1 = 0;
        for (int j = 0; j < 8; j++) {
            // checking horizontally
            if (grid[i][j] == 0) {
                counterH0++;
            } else {
                counterH0 = 0;
            }
            if (grid[i][j] == 1) {
                counterH1++;
            } else {
                counterH1 = 0;
            }

            // checking vertically
            if (grid[j][i] == 0) {
                counterV0++;
            } else {
                counterV0 = 0;
            }
            if (grid[j][i] == 1) {
                counterV1++;
            } else {
                counterV1 = 0;
            }
            if (counterH0 > 2 || counterH1 > 2 || counterV0 > 2 || counterV1 > 2) {
                return 0;
            }
        }
    }

    // check if there are identical rows or columns
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 8; j++) {
            int isIdenticalH = 1;
            int isIdenticalV = 1;
            for (int k = 0; k < 8; k++) {
                // check horizontally
                if (grid[i][k] != grid[j][k]) {
                    isIdenticalH = 0;
                }
                // check vertically
                if (grid[k][i] != grid[k][j]) {
                    isIdenticalV = 0;
                }
            }
            if (isIdenticalH || isIdenticalV) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int grid[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // reads digit by digit
            scanf("%1d", &grid[i][j]);
        }
    }

    if (checkCriteria(grid)) {
        printf("CORRECT\n");
    } else {
        printf("INCORRECT\n");
    }
}