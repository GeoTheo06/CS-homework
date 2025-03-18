/* file: red.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Mon Sep 23 2024 */
/* version: 1.0 */

/* Description: This program calculates how a roullete game will result if we apply the Martingale Red System with one euro as a starting price. The amount of money is given by the user.*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int money;
    scanf("%d", &money);
    int draw;
    scanf("%d", &draw);
    int currentBet = 1;
    while (draw != -1 && currentBet <= money) {
        // In number ranges from 1 to 10 and 19 to 28, odd numbers are red and even are black. In ranges from 11 to 18 and 29 to 36, odd numbers are black and even are red. Here I'm checking for red.
        if ((((draw >= 1 && draw <= 10) || (draw >= 19 && draw <= 28)) && draw % 2 == 1) || (((draw >= 11 && draw <= 18) || (draw >= 29 && draw <= 36)) && draw % 2 == 0)) {
            money += currentBet;
            currentBet = 1;
        } else {
            money -= currentBet;
            currentBet *= 2;
        }
        scanf("%d", &draw);
    }
    if (currentBet > money) {
        printf("BUST\n");
    } else {
        printf("%d\n", money);
    }
    return 0;
}
