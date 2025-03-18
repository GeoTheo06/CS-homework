/* file: smokingProblem.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Sep 17 2024 */
/* version: 1.0 */

/* Description:
 * This program counts how many ciggarettes a homeless man can smoke based on
 * how many butts he finds
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int butts;
    // read user input of butts
    scanf("%d", &butts);
    int cigs = 0;
    // loop for as long as there can be created at least one butt
    while (butts >= 4) {
        // add the new cigars to the total cigarettes counter
        cigs += butts / 4;
        // the new pile of butts will be the remaining butts from before that
        // couldn't be used because they were less than 4 plus the number of
        // cigarettes that can be created with the previous number of butts.
        butts = butts / 4 + butts % 4;
    }
    // print the total number of cigarettes
    printf("%d\n", cigs);
}