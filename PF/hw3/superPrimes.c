/* file: superPrimes.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Sep 25 2024 */
/* version: 1.0 */

/* Description: Checks if a number and the sum of the digits of a number and the
 * sum of the digits of every sum that occurs whenever the previous sum is still
 * bigger than 10 are prime.*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// culculates the sum of the digits of a number
int calcSum(int temp) {
  int sum = 0, digit;
  while (temp > 0) {
    digit = temp % 10;
    sum += digit;
    temp = temp / 10;
  }
  return sum;
}

// Checks if a  number is prime
bool checkIfPrime(int n) {
  if (n == 2) {
    return true;
  }
  if (n < 2) {
    return false;
  }
  if (n % 2 == 0) {
    return false;
  }
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int a, b;
  scanf("%d %d", &a, &b);
  int sum, counter = 0;
  bool isPrime;
  // runs for every number in the range a to b-1

  for (int i = a; i < b; i++) {
    sum = i;
    isPrime = true;
    // checks all the sums that are produced from previous sums that were
    // above 10.
    while (sum >= 10 && isPrime) {
      sum = calcSum(sum);
      isPrime = checkIfPrime(sum);
    }

    // check if the initial number is prime
    if (isPrime) {
      isPrime = checkIfPrime(i);
    }
    if (isPrime) {
      counter++;
    }
  }
  printf("%d\n", counter);
}