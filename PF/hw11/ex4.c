/* file: ex4.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Dec 19 2024 */
/* version: 1.0 */

/* Description: solves the Takuzu puzzle using a backtracking algorithm. fills the grid with 0s and 1s and ensures equal counts in rows and columns, no more than two identical numbers adjacent, and unique rows and columns. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 14

int n;
int grid[MAX_N][MAX_N];
int count0_row[MAX_N], count1_row[MAX_N];
int count0_col[MAX_N], count1_col[MAX_N];
int filled_rows[MAX_N][MAX_N], filled_rows_count = 0;
int filled_columns[MAX_N][MAX_N], filled_columns_count = 0;
bool solution_found = false;

// Function to print the grid
void print_grid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a row is unique among filled rows
bool is_unique_row(int row) {
    for (int r = 0; r < filled_rows_count; r++) {
        bool match = true;
        for (int c = 0; c < n; c++) {
            if (grid[row][c] != filled_rows[r][c]) {
                match = false;
                break;
            }
        }
        if (match) {
            return false;  // Not unique
        }
    }
    return true;  // Unique
}

// Function to check if a column is unique among filled columns
bool is_unique_column(int col) {
    for (int c = 0; c < filled_columns_count; c++) {
        bool match = true;
        for (int r = 0; r < n; r++) {
            if (grid[r][col] != filled_columns[c][r]) {
                match = false;
                break;
            }
        }
        if (match) {
            return false;  // Not unique
        }
    }
    return true;  // Unique
}

// Function to check if placing val at (i, j) is valid
bool is_valid(int i, int j, int val) {
    // Check row counts
    if (val == 0 && count0_row[i] + 1 > n / 2) {
        return false;
    }
    if (val == 1 && count1_row[i] + 1 > n / 2) {
        return false;
    }
    // Check column counts
    if (val == 0 && count0_col[j] + 1 > n / 2) {
        return false;
    }
    if (val == 1 && count1_col[j] + 1 > n / 2) {
        return false;
    }
    // Check row adjacency
    // Left two cells
    if (j >= 2 && grid[i][j - 1] == val && grid[i][j - 2] == val) {
        return false;
    }
    // Left and right cells
    if (j >= 1 && j < n - 1 && grid[i][j - 1] == val && grid[i][j + 1] == val) {
        return false;
    }
    // Right two cells
    if (j < n - 2 && grid[i][j + 1] == val && grid[i][j + 2] == val) {
        return false;
    }
    // Check column adjacency
    // Above two cells
    if (i >= 2 && grid[i - 1][j] == val && grid[i - 2][j] == val) {
        return false;
    }
    // Above and below cells
    if (i >= 1 && i < n - 1 && grid[i - 1][j] == val && grid[i + 1][j] == val) {
        return false;
    }
    // Below two cells
    if (i < n - 2 && grid[i + 1][j] == val && grid[i + 2][j] == val) {
        return false;
    }
    return true;
}

// Backtracking function to solve the Takuzu puzzle
bool backtrack() {
    if (solution_found) {
        return false;  // Solution already found
    }

    int i = -1, j = -1;

    // Find the next empty cell
    for (int x = 0; x < n && i == -1; x++) {
        for (int y = 0; y < n && i == -1; y++) {
            if (grid[x][y] == -1) {
                i = x;
                j = y;
            }
        }
    }

    // If no empty cells, print the solution
    if (i == -1) {
        print_grid();
        solution_found = true;
        return true;
    }

    // Try placing 0 and 1
    for (int val = 0; val <= 1; val++) {
        if (is_valid(i, j, val)) {
            // Place the value
            grid[i][j] = val;
            if (val == 0) {
                count0_row[i]++;
                count0_col[j]++;
            } else {
                count1_row[i]++;
                count1_col[j]++;
            }

            bool row_filled = false, column_filled = false;
            bool row_unique = true, column_unique = true;

            // Check if the row is filled
            if (count0_row[i] + count1_row[i] == n && count0_row[i] == n / 2 && count1_row[i] == n / 2) {
                row_filled = true;
                row_unique = is_unique_row(i);
            }

            // Check if the column is filled
            if (count0_col[j] + count1_col[j] == n && count0_col[j] == n / 2 && count1_col[j] == n / 2) {
                column_filled = true;
                column_unique = is_unique_column(j);
            }

            // Proceed only if uniqueness constraints are satisfied
            if (row_unique && column_unique) {
                if (row_filled) {
                    // Add the filled row to filled_rows
                    for (int c = 0; c < n; c++) {
                        filled_rows[filled_rows_count][c] = grid[i][c];
                    }
                    filled_rows_count++;
                }

                if (column_filled) {
                    // Add the filled column to filled_columns
                    for (int r = 0; r < n; r++) {
                        filled_columns[filled_columns_count][r] = grid[r][j];
                    }
                    filled_columns_count++;
                }

                // Recurse
                if (backtrack()) {
                    return true;
                }

                // Backtrack: Remove the filled row/column
                if (column_filled) {
                    filled_columns_count--;
                }
                if (row_filled) {
                    filled_rows_count--;
                }
            }

            // Undo the placement
            grid[i][j] = -1;
            if (val == 0) {
                count0_row[i]--;
                count0_col[j]--;
            } else {
                count1_row[i]--;
                count1_col[j]--;
            }
        }
    }

    return false;
}

int main() {
    // Read the grid size
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Read the grid
    char line[MAX_N + 2];  // +1 for newline, +1 for null terminator
    for (int i = 0; i < n; i++) {
        if (scanf("%s", line) != 1) {
            return 1;
        }
        for (int j = 0; j < n; j++) {
            if (line[j] == '.') {
                grid[i][j] = -1;
            } else if (line[j] == '0') {
                grid[i][j] = 0;
                count0_row[i]++;
                count0_col[j]++;
            } else if (line[j] == '1') {
                grid[i][j] = 1;
                count1_row[i]++;
                count1_col[j]++;
            } else {
                return 1;
            }
        }
    }

    // Initialize filled_rows and filled_columns based on the initial grid
    for (int i = 0; i < n; i++) {
        if (count0_row[i] + count1_row[i] == n && count0_row[i] == n / 2 && count1_row[i] == n / 2) {
            // Check for uniqueness only if there are already filled rows
            if (!is_unique_row(i)) {
                return 1;
            }
            for (int c = 0; c < n; c++) {
                filled_rows[filled_rows_count][c] = grid[i][c];
            }
            filled_rows_count++;
        }
    }

    for (int j = 0; j < n; j++) {
        if (count0_col[j] + count1_col[j] == n && count0_col[j] == n / 2 && count1_col[j] == n / 2) {
            // Check for uniqueness only if there are already filled columns
            if (!is_unique_column(j)) {
                return 1;
            }
            for (int r = 0; r < n; r++) {
                filled_columns[filled_columns_count][r] = grid[r][j];
            }
            filled_columns_count++;
        }
    }

    // Start backtracking to solve the puzzle
    backtrack();

    return 0;
}
