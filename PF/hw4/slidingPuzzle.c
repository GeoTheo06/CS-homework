/* file: slidingPuzzle.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Oct 02 2024 */
/* version: 1.1 */

/* Description: This program reads a sliding puzzle game state, stores it in a 2d array, then it reads some moves on the game, simulates the moves and prints if it is solved, unsolved, or if one of the moves that were inputted are wrong*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // read the first game state
    int n;
    scanf("%d", &n);

    // initializing array and allocating memory for each row
    int **grid = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grid[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    char move[5];
    int dig, row, col, tempI, tempJ;
    bool found, invalid = false;

    scanf("%s", move);
    while (move[0] != 'E' && !invalid) {
        scanf("%d", &dig);

        // searching for the position of the digit inputted
        tempI = 0;
        tempJ = 0;
        found = false;
        while (!found && tempI < n) {
            tempJ = 0;
            while (!found && tempJ < n) {
                if (dig == grid[tempI][tempJ]) {
                    found = true;
                    row = tempI;
                    col = tempJ;
                }
                tempJ++;
            }
            tempI++;
        }

        if (move[0] == 'U') {
            // check if we are on the first row (so going up will give out of bounds) and if the above tile has 0.
            if (row == 0 || grid[row - 1][col] != 0) {
                invalid = true;
            } else {
                grid[row][col] = 0;
                grid[row - 1][col] = dig;
            }
        } else if (move[0] == 'D') {
            if (row == n - 1 || grid[row + 1][col] != 0) {
                invalid = true;
            } else {
                grid[row][col] = 0;
                grid[row + 1][col] = dig;
            }
        } else if (move[0] == 'L') {
            if (col == 0 || grid[row][col - 1] != 0) {
                invalid = true;
            } else {
                grid[row][col] = 0;
                grid[row][col - 1] = dig;
            }
        } else if (move[0] == 'R') {
            if (col == n - 1 || grid[row][col + 1] != 0) {
                invalid = true;
            } else {
                grid[row][col] = 0;
                grid[row][col + 1] = dig;
            }
        }
        scanf("%s", move);
    }
    if (invalid) {
        printf("INVALID\n");
    } else {
        // checks if they are in ascending order by counting from 1 and upwards since we know that the tiles are numbered from 1 to n^2 -1
        int count = 1;
        bool solved = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 0 && count != grid[i][j]) {
                    solved = false;
                }
                if (grid[i][j] != 0) {
                    count++;
                }
            }
        }
        if (solved) {
            printf("SOLVED\n");
        } else {
            printf("UNSOLVED\n");
        }
    }

    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(grid[i]);  // Free each row
    }
    free(grid);  // Free the array of pointers
}