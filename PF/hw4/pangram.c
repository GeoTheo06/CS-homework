/* file: pangram.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Oct 02 2024 */
/* version: 1.0 */

/* Description: This program reads a sentence and outputs whether or not it is pangram*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // if all elements are 1 (exist) then it is, else it is not.
    char ab[26] = "00000000000000000000000000";
    char ch;

    scanf("%c", &ch);
    while (ch != '.') {
        // spaces don't count as alphabet and also it would try to access position under than 0 if i allowed it
        if (ch != ' ') {
            ab[ch - 65] = '1';
        }
        scanf("%c", &ch);
    }
    // check if all the elements in ab are 1.
    bool isPangram = true;
    for (int i = 0; i < 26; i++) {
        if (ab[i] == '0') {
            isPangram = false;
        }
    }
    if (isPangram) {
        printf("PANGRAM\n");
    } else {
        printf("NO PANGRAM\n");
    }
}