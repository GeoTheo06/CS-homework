/* file: ex5_suguru.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Fri Jan 10 2024 */
/* version: 1.0 */

/* Description: This program solves a Suguru puzzle on an nxm grid. The grid is divided into regions marked by letters, with each region having up to 9 cells. The goal is to fill the empty cells with numbers so that each region with k cells contains all numbers from 1 to k. It outputs the completed grid if a solution exists.*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int n, m;
static char regionLabel[12][12];   // Stores the region-letter for each cell
static int puzzle[12][12];         // Stores puzzle digits (0 if empty)
static int regionIndex[12][12];    // Maps each (row,col) to an integer region ID (0..25)
static int regionSize[26];         // Number of cells in each region
static bool usedInRegion[26][10];  // usedInRegion[r][d] = whether digit d used in region r

// Directions for adjacency (8 directions)
int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Check if a cell is within the grid boundaries
bool inBounds(int rr, int cc) {
    return (rr >= 0 && rr < n && cc >= 0 && cc < m);
}

// Check if placing digit 'd' at (r,c) violates the adjacency rule
// i.e., no neighbor (including diagonal) can have the same digit.
bool canPlace(int r, int c, int d) {
    for (int i = 0; i < 8; i++) {
        int rr = r + dr[i];
        int cc = c + dc[i];
        if (inBounds(rr, cc)) {
            if (puzzle[rr][cc] == d) {
                return false;
            }
        }
    }
    return true;
}

// Recursive backtracking function
bool solveSuguru(int cellIndex) {
    // If we've assigned all cells, we are done
    if (cellIndex == n * m) {
        return true;
    }

    int r = cellIndex / m;
    int c = cellIndex % m;

    // If this cell is already given/fixed, skip to next
    if (puzzle[r][c] != 0) {
        return solveSuguru(cellIndex + 1);
    }

    // Determine region & the region's size
    int reg = regionIndex[r][c];
    int k = regionSize[reg];  // We must place a digit in [1..k] in this region

    // Try each digit from 1..k
    for (int d = 1; d <= k; d++) {
        // If digit not already used in region and passes adjacency
        if (!usedInRegion[reg][d] && canPlace(r, c, d)) {
            // Place it
            puzzle[r][c] = d;
            usedInRegion[reg][d] = true;

            // Recurse
            if (solveSuguru(cellIndex + 1)) {
                return true;
            }

            // Backtrack
            puzzle[r][c] = 0;
            usedInRegion[reg][d] = false;
        }
    }

    // If no digit 1..k worked, fail
    return false;
}

// Maps region labels (A,B,C,...) to integer indexes (0..25)
int labelToIndex(char ch) {
    return (int)(ch - 'A');
}

int main(void) {
    // Read n, m
    if (scanf("%d %d", &n, &m) != 2) {
        printf("UNSOLVABLE\n");
        return 0;
    }
    // Read region labeling
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &regionLabel[i][j]);
        }
    }

    // Convert region labeling (letters) to region indices and track region sizes
    memset(regionSize, 0, sizeof(regionSize));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int idx = labelToIndex(regionLabel[i][j]);
            regionIndex[i][j] = idx;
            regionSize[idx]++;
        }
    }

    // Read puzzle givens; store 0 if '.'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch;
            scanf(" %c", &ch);
            if (ch == '.') {
                puzzle[i][j] = 0;
            } else {
                puzzle[i][j] = ch - '0';  // convert char digit to int
            }
        }
    }

    // Initialize usedInRegion
    memset(usedInRegion, false, sizeof(usedInRegion));

    // Mark used digits in each region from the givens
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int d = puzzle[i][j];
            if (d != 0) {
                int reg = regionIndex[i][j];
                if (d > regionSize[reg] || usedInRegion[reg][d]) {
                    printf("UNSOLVABLE\n");
                    return 0;
                }
                usedInRegion[reg][d] = true;
            }
        }
    }

    if (solveSuguru(0)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d", puzzle[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("UNSOLVABLE\n");
    }

    return 0;
}
