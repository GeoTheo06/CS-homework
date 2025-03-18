/* file: divisibleBy13.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Sep 17 2024 */
/* version: 1.0 */

/* Description: This program inputs a random positive integer and outputs if it
 * is divisable by 13 and shows the steps it took to find if it is divisable*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    // read input number
    scanf("%d", &n);
    int lastDigit;
    // Loop to process the number until it becomes a two-digit number
    while (n >= 100) {
        printf("%d->", n);
        lastDigit = n % 10;  // Extract the last digit of the current number
        n = n / 10;          // Remove the last digit from the number
        n = n + (lastDigit * 4);
    }
    int multiple = n / 13;
    int remainder = n % 13;
    // Output the final computation in the form of 'number = quotient * 13 +
    // remainder'
    printf("%d=%d*13+%d\n", n, multiple, remainder);
    if (remainder == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}