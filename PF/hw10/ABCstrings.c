/* file: prob1.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Nov 04 2024 */
/* version: 1.0 */

/* Description: This program generates recursively all combinations of a wildcard pattern with 'A', 'B', 'C', and '?', where '?' can be any of the three letters.*/

#include <stdio.h>
#include <stdlib.h>

void createCombinations(char pattern[33], int index) {
    // base case
    if (pattern[index] == '.') {
        // print the created string
        int count = 0;
        printf("%c", pattern[count]);
        count++;
        while (pattern[count] != '.') {
            printf("%c", pattern[count]);
            count++;
        }
        printf("\n");

        return;
    }

    if (pattern[index] == '?') {
        char possibleValues[3] = {'A', 'B', 'C'};
        for (int i = 0; i < 3; i++) {
            pattern[index] = possibleValues[i];
            createCombinations(pattern, index + 1);
        }
        // reset the position so it starts from A in the next occurence
        pattern[index] = '?';
    } else {
        // nothing happened in this index so continue in the next
        createCombinations(pattern, index + 1);
    }
}

int main(int argc, char *argv[]) {
    char pattern[33];
    char temp;
    // read the pattern
    scanf("%c", &temp);
    int count = 0;
    while (temp != '\n') {
        pattern[count] = temp;
        scanf("%c", &temp);
        count++;
    }
    pattern[count] = '.';
    createCombinations(pattern, 0);
}