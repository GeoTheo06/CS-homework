/* file: assembly.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Oct 02 2024 */
/* version: 1.0 */

/* Description: This program reads 8 assembly commands and simulates them in c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// reads the name of the register
char readReg() {
    char ch;
    char temp;
    // reads R
    scanf("%c", &temp);
    // reads number
    scanf("%c", &ch);
    // reads space or \n
    scanf("%c", &temp);
    return ch;
}

// does all 3 possible calculations
int calc(char reg1, char reg2, int r1, int r2, char sym) {
    if (reg1 == '1' && reg2 == '2') {
        if (sym == '+') {
            return r1 + r2;
        } else if (sym == '-') {
            return r1 - r2;
        } else if (sym == '*') {
            return r1 * r2;
        }
    } else if (reg1 == '1' && reg2 == '1') {
        if (sym == '+') {
            return r1 + r1;
        } else if (sym == '-') {
            return r1 - r1;
        } else if (sym == '*') {
            return r1 * r1;
        }
    } else if (reg1 == '2' && reg2 == '1') {
        if (sym == '+') {
            return r2 + r1;
        } else if (sym == '-') {
            return r2 - r1;
        } else if (sym == '*') {
            return r2 * r1;
        }
    } else if (reg1 == '2' && reg2 == '2') {
        if (sym == '+') {
            return r2 + r2;
        } else if (sym == '-') {
            return r2 - r2;
        } else if (sym == '*') {
            return r2 * r2;
        }
    }
    return 0;
}

int main() {
    char sent = ' ', reg, reg1, reg2;
    int r1, r2;
    char temp;
    while (sent != 'E') {
        // read the first letter and then just discard the others up to space.
        scanf("%c", &sent);
        scanf("%c", &temp);
        scanf("%c", &temp);
        scanf("%c", &temp);
        if (sent == 'L') {
            reg = readReg();
            if (reg == '1') {
                scanf("%d", &r1);
            } else if (reg == '2') {
                scanf("%d", &r2);
            }
            scanf("%c", &temp);
        } else if (sent == 'A') {
            reg1 = readReg();
            reg2 = readReg();
            if (reg2 == '1') {
                r1 = calc(reg1, reg2, r1, r2, '+');
            } else {
                r2 = calc(reg1, reg2, r1, r2, '+');
            }
        } else if (sent == 'M') {
            reg1 = readReg();
            reg2 = readReg();
            if (reg2 == '1') {
                r1 = calc(reg1, reg2, r1, r2, '*');
            } else {
                r2 = calc(reg1, reg2, r1, r2, '*');
            }
        } else if (sent == 'S') {
            reg1 = readReg();
            reg2 = readReg();
            if (reg2 == '1') {
                r1 = calc(reg1, reg2, r1, r2, '-');
            } else {
                r2 = calc(reg1, reg2, r1, r2, '-');
            }
        } else if (sent == 'I') {
            reg = readReg();
            if (reg == '1') {
                r1++;
            } else {
                r2++;
            }
        } else if (sent == 'D') {
            reg = readReg();
            if (reg == '1') {
                r1--;
            } else {
                r2--;
            }
        } else if (sent == 'O') {
            reg = readReg();
            if (reg == '1') {
                printf("%d\n", r1);
            } else {
                printf("%d\n", r2);
            }
        }
    }
}