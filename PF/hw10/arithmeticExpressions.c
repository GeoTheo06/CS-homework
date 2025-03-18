/* file: airhtmeticExpressions.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Nov 05 2024 */
/* version: 1.0 */

/* Description: calculates how many arithmetic expressions evaluate to n using the digits 1 to 9 and the operators +, -, and *. It uses recursion to explore all possible combinations of operators */

#include <stdio.h>

int target;

int count_expressions(int index, int sum, int lastFactor) {
    // If we've placed operations between all digits up to 9
    if (index == 10) {
        // If the total after adding the last factor matches the target, count it
        if (sum + lastFactor == target) {
            return 1;
        } else {
            return 0;
        }
    }

    int count = 0;

    // Add the lastFactor to sum, reset lastFactor to the current index
    count += count_expressions(index + 1, sum + lastFactor, index);

    // Add the lastFactor to sum, reset lastFactor to negative of current index
    count += count_expressions(index + 1, sum + lastFactor, -index);

    // Multiply the lastFactor by current index
    count += count_expressions(index + 1, sum, lastFactor * index);

    return count;
}

int main() {
    scanf("%d", &target);
    // Start with the first digit '1'.
    int result = count_expressions(2, 0, 1);
    printf("%d\n", result);
    return 0;
}
