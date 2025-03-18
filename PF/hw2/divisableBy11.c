/* file: divisibleBy11.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Sep 19 2024 */
/* version: 1.1 */

/* Description: This program inputs a positive integer and outputs if it
 * is divisable by 11 and shows the steps it took to find if it is divisable*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    char digit;
    int sum = 0;

    int count = 1;
    // will read each digit one by one in char because 10^1000 doesn't fit in
    // any known data type
    scanf("%c", &digit);
    // looping for as long as we haven't reached the end
    while (digit != '\n') {
        //
        if (count % 2 == 1) {
            // subtract '0' because in ascii it's 48 and the numbers start after
            // that so subtracting their ascii values will give the actual
            // number
            printf("+%d", digit - '0');
            sum += digit - '0';
        } else {
            printf("-%d", digit - '0');
            sum -= digit - '0';
        }
        scanf("%c", &digit);
        count++;
    }
    printf("=%d\n", sum);
    // change the sign of sum if its negative
    if (sum < 0) {
        sum = -sum;
    }
    int n = sum;
    sum = 0;

    if (n >= 11) {
        do {
            // calculate the number of digits that sum has
            int temp = n;
            int nDigits = 0;
            while (temp > 0) {
                temp = temp / 10;
                nDigits++;
            }
            sum = 0;
            for (int i = nDigits; i > 0; i--) {
                // the 2 for loops in combination give me the specific number in
                // the order of n I want.
                int lastDigit = n;
                // Basically, the first loop loops from the end of the
                // number to the beginning while dividing it. iterates to the
                // next single digit number in n because i gets smaller.
                for (int k = 0; k < i - 1; k++) {
                    lastDigit = lastDigit / 10;
                }

                // the second loop loops from beginning to end of n and
                // everytime
                //  it iterates to the next single digit number in n because i
                //  gets smaller, so I increment the counter till it reaches
                //  nDigits -i.
                for (int k = 0; k < nDigits - i; k++) {
                    lastDigit = lastDigit % 10;
                }
                // using i to check how many iterations we have done so far. if
                // the number of iterations is even then the single digid number
                // is in the even order of n so I want to add it to sum.
                // Opposite case happens for odds
                if ((nDigits - i + 1) % 2 == 1) {
                    printf("+%d", lastDigit);
                    sum += lastDigit;
                } else {
                    printf("-%d", lastDigit);
                    sum -= lastDigit;
                }
            }
            printf("=%d\n", sum);
            // change the sign of sum if its negative
            if (sum < 0) {
                sum = -sum;
            }
            // i will need this for the next iteration in case sum is bigger
            // than 11
            n = sum;
        } while (sum >= 11);
    }

    // n = sum so I can use either one
    if (n == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}