/* file: nDigits.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Sep 24 2024 */
/* version: 1.0 */

/* Description: This program calculates the last n digits of a number to the
 * power of another number (big enough to not fit inside any variable most of
 * the times) when modded by a specified (n) power of 10. It uses modular
 * exponentiation rules to calculate the last digits without overflowing*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int a, e, n;
  scanf("%d %d %d", &a, &e, &n);

  int divisor = 1;
  // calculate the number with which a^e will be modded with so we can get the
  // respective number of digits
  for (int i = 0; i < n; i++) {
    divisor = divisor * 10;
  }
  int multiplier = 1;
  // looping until we have split the number to a multiple and the number to the
  // power of 1.
  while (e > 1) {
    // we can simplify a because it will be modded by the divisor
    // anyways
    if (a > divisor) {
      a = a % divisor;
    }
    // we can simplify the multiplier because it will be modded by the divisor
    // anyways
    if (multiplier > divisor) {
      multiplier = multiplier % divisor;
    }

    if (e % 2 == 0) {
      // simplify the number using exponentiation rules
      e = e / 2;
      a = a * a;
    } else {  // if e is not divisable with 2 we can't divide it because we will
              // lose one digit. Instead we can use the following property:
      // using the modular exponentiation property
      e--;
      multiplier *= a;
    }
  }

  int nDigits = (a % divisor) * multiplier;

  // printing the last n digits one by one so I don't miss the 0s.
  for (int i = 0; i < n; i++) {
    // extracting the specific digit i want by dividing as many times to reach
    // the digit (until i have the number up to that digit) and then modding it
    // to get the actual last digit from that temporary number
    int temp = nDigits;
    for (int k = i; k < n - 1; k++) {
      temp = temp / 10;
    }
    temp = temp % 10;
    printf("%d", temp);
  }
  printf("\n");
}