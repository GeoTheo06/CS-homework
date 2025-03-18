/* file: bounding_box.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Sep 12 2024 */
/* version: 1.0 */

/* Description: 
 * This program prints the bottom left corner point and the top right corner point 
 * of the bounding box of three circles whose coordinates and radii are given as input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int x1;
    int y1;
    int rad1;
    int x2;
    int y2;
    int rad2;
    int x3;
    int y3;
    int rad3;
    int maxDown;
    int maxLeft;
    int maxRight;
    int maxUp;

    // Reading input values for three circles
    scanf("%d %d %d", &x1, &y1, &rad1);
    scanf("%d %d %d", &x2, &y2, &rad2);
    scanf("%d %d %d", &x3, &y3, &rad3);

    // Finding the minimum left coordinate
    maxLeft = x1 - rad1;
    if (x2 - rad2 < maxLeft) {
        maxLeft = x2 - rad2;
    }
    if (x3 - rad3 < maxLeft) {
        maxLeft = x3 - rad3;
    }

    // Finding the maximum right coordinate
    maxRight = x1 + rad1;
    if (x2 + rad2 > maxRight) {
        maxRight = x2 + rad2;
    }
    if (x3 + rad3 > maxRight) {
        maxRight = x3 + rad3;
    }

    // Finding the maximum up coordinate
    maxUp = y1 + rad1;
    if (y2 + rad2 > maxUp) {
        maxUp = y2 + rad2;
    }
    if (y3 + rad3 > maxUp) {
        maxUp = y3 + rad3;
    }

    // Finding the minimum down coordinate
    maxDown = y1 - rad1;
    if (y2 - rad2 < maxDown) {
        maxDown = y2 - rad2;
    }
    if (y3 - rad3 < maxDown) {
        maxDown = y3 - rad3;
    }

    // Printing the bottom left and top right corner of the bounding box
    printf("[(%d,%d),(%d,%d)]\n", maxLeft, maxDown, maxRight, maxUp);

    return 0;
}
