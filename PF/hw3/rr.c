/* file: rr.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Sep 26 2024 */
/* version: 1.0 */

/* Description: The program inputs 2 clauses from the user and checks if they
 * have a complement. If they do, the program will output the resolvent of the
 * two clauses with no letters duplicated. If they don't the program will output
 * "NO RESOLVENTS"*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // I will represent each letter of the alphabet with one of the three possible values. 1 indicates empty, 2 indicates positive number, 3 indicates negative number.
    char clause1[27] = "11111111111111111111111111";
    char clause2[27] = "11111111111111111111111111";
    char res[27] = "11111111111111111111111111";
    char ch;
    int pos;
    // scans the '[]' character
    scanf("%c", &ch);

    // read first clause and update the clause1 values accordingly
    while (ch != ']') {
        if (ch != '[' && ch != ',') {
            if (ch == '~') {
                scanf("%c", &ch);
                pos = ch - 65;
                clause1[pos] = '3';
            } else {
                pos = ch - 65;
                clause1[pos] = '2';
            }
        }
        scanf("%c", &ch);
    }

    scanf("%c", &ch);

    // read first clause and update the clause1 values accordingly
    while (ch != ']') {
        if (ch != '[' && ch != ',') {
            if (ch == '~') {
                scanf("%c", &ch);
                pos = ch - 65;
                clause2[pos] = '3';
            } else {
                pos = ch - 65;
                clause2[pos] = '2';
            }
        }
        scanf("%c", &ch);
    }
    bool complements = false;

    // make the resolvent from the two clauses
    for (int i = 0; i < 26; i++) {
        if ((clause1[i] == '2' || clause1[i] == '3') && res[i] == '1') {
            res[i] = clause1[i];
        } else if ((clause1[i] == '3' && res[i] == '2') || (clause1[i] == '2' && res[i] == '3')) {
            complements = true;
            res[i] = '1';
        }
    }
    for (int i = 0; i < 26; i++) {
        if ((clause2[i] == '2' || clause2[i] == '3') && res[i] == '1') {
            res[i] = clause2[i];
        } else if ((clause2[i] == '3' && res[i] == '2') || (clause2[i] == '2' && res[i] == '3')) {
            complements = true;
            res[i] = '1';
        }
    }
    // print the (possible) resolvent
    bool firstElement = false;
    if (complements) {
        printf("[");
        for (int i = 0; i < 26; i++) {
            if (res[i] == '2') {
                if (!firstElement) {
                    firstElement = true;
                } else {
                    printf(",");
                }
                printf("%c", i + 65);
            } else if (res[i] == '3') {
                if (!firstElement) {
                    firstElement = true;
                } else {
                    printf(",");
                }
                printf("~%c", i + 65);
            }
        }
        printf("]\n");
    } else {
        printf("NO RESOLVENT\n");
    }
}