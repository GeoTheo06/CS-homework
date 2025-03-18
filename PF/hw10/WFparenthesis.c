/* file: WFparenthesis.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Nov 04 2024 */
/* version: 1.0 */

/* Description: calculates the number of well-formed parentheses strings of n length, using recursion and dynamic programming. If n is odd, it outputs 0, because odd strings need even length.*/
#include <stdio.h>

int dp[100];

int sum(int k) {
    // If already calculated, return it
    if (dp[k] != -1) {
        return dp[k];
    }

    if (k == 0) {
        dp[k] = 1;
        return 1;
    }

    int result = 0;
    for (int i = 0; i < k; i++) {
        result += sum(i) * sum(k - 1 - i);
    }

    dp[k] = result;
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    // If odd length, no well-formed parentheses possible
    if (n % 2 != 0) {
        printf("0\n");
        return 0;
    }

    // Initialize dp array
    for (int i = 0; i < 100; i++) {
        dp[i] = -1;
    }

    int half = n / 2;
    int answer = sum(half);
    printf("%d\n", answer);

    return 0;
}