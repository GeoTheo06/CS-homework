/* file: ppp.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Sep 26 2024 */
/* version: 1.0 */

/* Description: This program inputs a number and checks whether it is
 * palindromic, prime and proth (every number of the form k*2n + 1). If it is
 * not proth, it doesn't matter about the other 2 checks */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isProth(int num) {
  num = num - 1;

  int k = num;
  int n = 0;

  // calcualating k and n
  while (k % 2 == 0) {
    k = k / 2;
    n++;
  }

  // k and n have to be positive integers for a number to be proth
  if (k == 0 || n == 0) {
    return false;
  }

  //  calculate the power of 2 which gives k so I can compare it later with n
  //  (which is also a power of 2)
  int logK = k;
  int kExponent = 0;
  while (logK > 1) {
    logK = logK / 2;
    kExponent++;
  }

  if (kExponent < n) {
    return true;
  } else {
    return false;
  }
}

bool isPrime(int n) {
  if (n < 2) {
    return false;
  }
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {  // this case is excluded in the main check in the for loop
    return false;
  }
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

// extracts the ith digit from a number n
int extractDigit(int n, int pos) {
  for (int i = 0; i < pos; i++) {
    n = n / 10;
  }
  return n % 10;
}

bool isPalindromic(int n) {
  // calculate digits of n
  int temp = n;
  int digits = 0;
  while (temp > 0) {
    temp = temp / 10;
    digits++;
  }
  int dig1, dig2;

  // it will check the number from the front and from the back at the same time
  // until they both reach the middle.
  for (int i = 0; i < digits / 2; i++) {
    dig1 = extractDigit(n, digits - i - 1);
    dig2 = extractDigit(n, i);
    if (dig1 != dig2) {
      return false;
    }
  }
  return true;
}

int main() {
  int n;

  scanf("%d", &n);

  bool proth = isProth(n);
  if (proth) {
    bool prime = isPrime(n), palindromic = isPalindromic(n);
    if (palindromic) {
      printf("%d is a palindromic Proth ", n);
    } else {
      printf("%d is a Proth ", n);
    }
    if (prime) {
      printf("prime.\n");
    } else {
      printf("number.\n");
    }
  } else {
    printf("%d is not a Proth number.\n", n);
  }
}