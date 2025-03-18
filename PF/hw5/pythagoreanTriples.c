/* file: pythagoreanTriples.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Oct 08 2024 */
/* version: 1.0 */

/* Description: This program reads a number n and outputs all the primitive triples such that a+b+c = n*/

#include <stdio.h>
#include <stdlib.h>

// calculates greatest common divisor
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int in;
    scanf("%d", &in);
    int counter = 0;
    // For two positive integers m and n where m > n, m and n are coprime, and not both odd, the triple is given by: a= m^2 - n^2, b = 2mn, c = m^2 + n^2. Simplified it is 2m(m+n)
    for (int m = 2; m < in; m++) {
        for (int n = 1; n < m; n++) {
            if (gcd(m, n) == 1 && (m % 2 == 0 || n % 2 == 0) && 2 * m * (m + n) == in) {
                counter++;
            }
            if (2 * m * (m + n) > in) {
                break;
            }
        }
    }
    printf("%d\n", counter);
}