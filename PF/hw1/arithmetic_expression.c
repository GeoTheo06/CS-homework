/* file: arithmetic_expression.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Sep 12 2024 */
/* version: 1.0 */

/* Description:
 * This program outputs the result of the operations between 3 numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int num1;
    int num2;
    int num3;
    char op1;
    char op2;
    int result;

    // Reading input in the form of num1 op1 num2 op2 num3
    scanf("%d%c%d%c%d", &num1, &op1, &num2, &op2, &num3);

    // If the first operator is *, we first multiply num1 and num2
    if (op1 == '*') {
        result = num1 * num2;
        // Then, based on op2, either add or multiply the result with num3
        if (op2 == '+') {
            result += num3;
        } else { // op2 is *
            result *= num3;
        }
    } else { // op1 is +, we handle it differently
        // If op2 is +, add num2 and num3 first
        if (op2 == '+') {
            result = num2 + num3;
        } else { // op2 is *
            result = num2 * num3;
        }
        // Then add num1 to the result
        result += num1;
    }

    // Output the result of the operations
    printf("%d\n", result);

    return 0;
}
