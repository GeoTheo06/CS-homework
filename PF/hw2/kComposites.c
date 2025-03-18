/* file: kComposites.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Tue Wed 18 2024 */
/* version: 1.0 */

/* Description: finds the smallest number kComposite that is divisable by all
 * previous numbers oin the range 1-k. k is given by input
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // read input
    int k;
    scanf("%d", &k);
    int i = 0;
    int kComposite = 0;
    // k will reach i when the second while loop terminates because of !(i<k)
    while (i < k) {
        // I will only check the multiples of k. This means that in the
        // loop where I check all numbers, I want have to check k
        // because it is for sure a multiple of k
        kComposite += k;
        i = 1;
        // checking if it is divisable by all numbers in the range 1 to k-1
        while (i < k && kComposite % i == 0) {
            i++;
        }
    }
    printf("%d\n", kComposite);
}