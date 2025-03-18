/* file: camping.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Sep 12 2024 */
/* version: 1.0 */

/* Description:
 * This program calculates the number of trips the father needs to go to the water tap,
 * fill the 2 jerrycans, and go back to the pool to throw the water.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    // Asking for total liters of water
    int litres;
    scanf("%d", &litres);

    int walks;
    // Calculating the number of trips needed
    if (litres % 24 == 0) {
        walks = litres / (12 * 2);
    } else {
        walks = litres / (12 * 2) + 1;
    }

    // Output the number of trips
    printf("%d\n", walks);

    return 0;
}
