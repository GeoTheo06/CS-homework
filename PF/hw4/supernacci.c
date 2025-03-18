/* 	file: supernacci.c
    author: George Theodoridis (g.theodoridis@rug.nl)
    date: Sun Oct 06 2024
    version: 1.0

   Description:
     This programma accepts on its input a positive integer n,
     and outputs fib(n). The program works as longs as the
     number of digits of fib(n) does not exceed 1000.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXDIG 1000

typedef struct {
    int numDigits;       // number of digits
    int digits[MAXDIG];  // decimal digits of big integer
} unsignedBigInt;

unsignedBigInt makeUnsignedBigIntFromInt(unsigned int n) {
    unsignedBigInt converter;
    int temp = n;
    int counter = 0;

    // splitting the n to single digits starting from the end and putting them into the digits array.
    while (temp > 0) {
        converter.digits[counter] = temp % 10;
        temp /= 10;
        counter++;
    }
    // number of digits should start from 1 and also if n is 0 the loop will not run so it will think there are no digits.

    converter.numDigits = counter + 1;
    return converter;
}

void printBigInt(unsignedBigInt big) {
    for (int i = big.numDigits - 1; i >= 0; i--) {
        printf("%d", big.digits[i]);
    }
}

void printlnBigInt(unsignedBigInt big) {
    int reachedNum = 0;
    for (int i = big.numDigits - 1; i >= 0; i--) {
        // I don't want to print the first 0s
        if (!reachedNum && big.digits[i] != 0) {
            reachedNum = 1;
        }
        if (reachedNum || big.digits[i] != 0) {
            printf("%d", big.digits[i]);
        }
    }
    printf("\n");
}

unsignedBigInt add(unsignedBigInt a, unsignedBigInt b) {
    unsignedBigInt res;
    int addOne = 0, maxDigits, digA, digB;
    // find the biggest number between a and b
    if (a.numDigits > b.numDigits) {
        maxDigits = a.numDigits;
    } else {
        maxDigits = b.numDigits;
    }

    res.numDigits = 0;

    // "|| addOne" is for the case where the number with the less digits is over and there is still a +1 from its last digit.
    for (int i = 0; i < maxDigits || addOne; i++) {
        // In the case of addition I don't know which of the 2 numbers is bigger
        if (i < a.numDigits) {
            digA = a.digits[i];
        } else {
            digA = 0;
        }
        if (i < b.numDigits) {
            digB = b.digits[i];
        } else {
            digB = 0;
        }

        int sum = digA + digB + addOne;

        res.digits[i] = sum % 10;

        // handle the +1 on the next digit case
        if (sum >= 10) {
            addOne = 1;
        } else {
            addOne = 0;
        }
        res.numDigits++;
    }

    return res;
}

unsignedBigInt subtract(unsignedBigInt a, unsignedBigInt b) {
    unsignedBigInt res;
    int addOne = 0;
    int i = 0;
    int digA, digB;
    for (i = 0; i < a.numDigits; i++) {
        digA = a.digits[i];

        if (i < b.numDigits) {
            digB = b.digits[i];
        } else {
            digB = 0;
        }

        int sub = digA - digB - addOne;

        // handle the +1 case
        if (sub < 0) {
            sub += 10;
            addOne = 1;
        } else {
            addOne = 0;
        }

        res.digits[i] = sub;
    }

    res.numDigits = a.numDigits;

    // remove additional zeroes
    while (res.numDigits > 1 && res.digits[res.numDigits - 1] == 0) {
        res.numDigits--;
    }

    return res;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    printf("fib(%d)=", n);

    unsignedBigInt a = makeUnsignedBigIntFromInt(0);
    unsignedBigInt b = makeUnsignedBigIntFromInt(1);

    while (n > 0) {
        b = add(a, b);
        a = subtract(b, a);
        n--;
    }

    printlnBigInt(a);
    return 0;
}