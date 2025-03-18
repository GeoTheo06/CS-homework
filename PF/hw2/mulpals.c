/* file: mulpals.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Sep 18 2024 */
/* version: 1.0 */

/* Description:
This program finds how many mulpals (mulpal = number that if multiplied with a
specific number, the result is the mulpal but the digits are turnt the other way
round) exist in a specific range that is given by input
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a;
    int b;
    int mulpals = 0;
    // read the range of numbers
    scanf("%d %d", &a, &b);

    // Repeating the same process for every number within the range
    for (int i = a; i <= b; i++) {
        // reversing each number
        int temp = i;
        // gives me the last digit of i
        int iReversed = temp % 10;
        while (temp >= 10) {
            temp = temp / 10;
            iReversed = iReversed * 10 + temp % 10;
        }
        // if and only if there is an integer that multiplied with the given
        // number gives the mulpal then it is divisable by it
        if (iReversed % i == 0) {
            // incrementing the mulpals counter
            mulpals += 1;
        }
    }

    printf("%d\n", mulpals);
}