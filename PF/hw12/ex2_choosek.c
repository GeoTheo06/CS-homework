/* file: ex2_choosek.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Jan 09 2024 */
/* version: 1.0 */

/* Description: This program calculates the binomial coefficient C(2024,k) modulo 2025 using dynamic programming.*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int k;
    scanf("%d", &k);

    long long *C = (long long *)malloc(sizeof(long long) * k + 1);
    for (int i = 0; i < k + 1; i++) {
        C[i] = 0;
    }

    C[0] = 1;  // C(n, 0) is always 1

    for (int n = 1; n <= 2024; n++) {
        int upper = (n < k) ? n : k;
        for (int j = upper; j > 0; j--) {
            C[j] = (C[j] + C[j - 1]) % 2025;
        }
        // C[j] for j > n is 0, so no need to handle them
    }

    printf("%lld\n", C[k]);
    return 0;
}