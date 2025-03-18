/* file: updown.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Nov 05 2024 */
/* version: 1.0 */

/* Description: Counts permutations of integers 1 to n that alternate between increasing and decreasing values. It uses recursion and backtracking to generate the up-down pattern */
#include <stdbool.h>
#include <stdio.h>

int n;
bool used[12];
int permutation[12];
int countSolutions = 0;

void backtrack(int pos) {
    // If we placed all numbers, we found a valid permutation
    if (pos > n) {
        countSolutions++;
        return;
    }

    for (int num = 1; num <= n; num++) {
        if (!used[num]) {
            bool valid = true;
            if (pos > 1) {
                if (pos % 2 == 0) {
                    // even position should be greater than previous
                    if (permutation[pos - 1] >= num) {
                        valid = false;
                    }
                } else {
                    // odd position should be smaller
                    if (permutation[pos - 1] <= num) {
                        valid = false;
                    }
                }
            }

            if (valid) {
                // if valid continue with the next position
                used[num] = true;
                permutation[pos] = num;
                backtrack(pos + 1);
                used[num] = false;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    // Initialize global variables
    for (int i = 1; i <= n; i++) {
        used[i] = false;
    }
    countSolutions = 0;

    // We need to start with each possible number for position 1
    // No constraints for the first position
    for (int i = 1; i <= n; i++) {
        used[i] = true;
        permutation[1] = i;
        backtrack(2);
        used[i] = false;
    }

    printf("%d\n", countSolutions);
    return 0;
}
