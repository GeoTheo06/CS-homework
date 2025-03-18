/* file: ex2.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Dec 19 2024 */
/* version: 1.0 */

/* Description: solves cryptarithmetic multiplication puzzle where letters represent digits, and the goal is to find a digit assignment that satisfies the given equation. Its using backtracking to assign unique digits to letters. If a solution exists it prints it, otherwise it outputs "UNSOLVABLE."*/
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char left1[50], left2[50], right[50];
char letters[26];  // stores distinct letters
int letterCount = 0;
bool usedDigit[10];
int letterDigit[26];  // letter to digit
bool solutionFound = false;

// Array to store found solutions
#define MAX_SOLUTIONS 100000
char solutions[MAX_SOLUTIONS][300];
int solutionCount = 0;

// Convert a word (with letters) to an integer using the current letter->digit mapping
long long wordToValue(const char *word) {
    long long val = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        int index = (int)(strchr(letters, c) - letters);
        val = val * 10 + letterDigit[index];
    }
    return val;
}

// Check leading zeros constraint
bool validLeadingZeros(void) {
    if (left1[0] && letterDigit[strchr(letters, left1[0]) - letters] == 0 && strlen(left1) > 1) {
        return false;
    }
    if (left2[0] && letterDigit[strchr(letters, left2[0]) - letters] == 0 && strlen(left2) > 1) {
        return false;
    }
    if (right[0] && letterDigit[strchr(letters, right[0]) - letters] == 0 && strlen(right) > 1) {
        return false;
    }
    return true;
}

void storeSolution(void) {
    // We need to print letters in alphabetical order with their assigned digits.
    // letters[] is already sorted alphabetically.

    char line[300];
    line[0] = '\0';
    for (int i = 0; i < letterCount; i++) {
        char c = letters[i];
        int index = (int)(strchr(letters, c) - letters);
        char part[10];
        snprintf(part, sizeof(part), "%c=%d", c, letterDigit[index]);
        strcat(line, part);
        if (i < letterCount - 1) strcat(line, ",");
    }

    strcpy(solutions[solutionCount++], line);
}

// Backtracking function to assign digits to letters
void backtrack(int pos) {
    if (pos == letterCount) {
        // All letters assigned, check the equation
        if (!validLeadingZeros()) {
            return;
        }

        long long val1 = wordToValue(left1);
        long long val2 = wordToValue(left2);
        long long val3 = wordToValue(right);

        if (val1 * val2 == val3) {
            solutionFound = true;
            storeSolution();
        }
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (!usedDigit[i]) {
            usedDigit[i] = true;
            letterDigit[pos] = i;
            backtrack(pos + 1);
            usedDigit[i] = false;
        }
    }
}

int main(void) {
    char input[200];
    if (scanf("%199s", input) != 1) {
        printf("UNSOLVABLE\n");
        return 0;
    }

    // Find '*' and '='
    char *mulPos = strchr(input, '*');
    char *eqPos = strchr(input, '=');

    if (!mulPos || !eqPos) {
        // Invalid format
        printf("UNSOLVABLE\n");
        return 0;
    }

    *mulPos = '\0';  // split
    *eqPos = '\0';   // split

    strcpy(left1, input);
    strcpy(left2, mulPos + 1);
    strcpy(right, eqPos + 1);

    // Extract distinct letters
    bool present[256];
    for (int i = 0; i < 256; i++) present[i] = false;

    // Extract letters
    for (int i = 0; left1[i]; i++) {
        if (isalpha((unsigned char)left1[i]) && !present[(unsigned char)left1[i]]) {
            present[(unsigned char)left1[i]] = true;
            letters[letterCount++] = left1[i];
        }
    }
    for (int i = 0; left2[i]; i++) {
        if (isalpha((unsigned char)left2[i]) && !present[(unsigned char)left2[i]]) {
            present[(unsigned char)left2[i]] = true;
            letters[letterCount++] = left2[i];
        }
    }
    for (int i = 0; right[i]; i++) {
        if (isalpha((unsigned char)right[i]) && !present[(unsigned char)right[i]]) {
            present[(unsigned char)right[i]] = true;
            letters[letterCount++] = right[i];
        }
    }

    // we only have digits 0-9.
    if (letterCount > 10) {
        printf("UNSOLVABLE\n");
        return 0;
    }

    // Sort letters alphabetically before assigning digits
    for (int i = 0; i < letterCount - 1; i++) {
        for (int j = i + 1; j < letterCount; j++) {
            if (letters[i] > letters[j]) {
                char temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }
        }
    }

    // Backtracking to assign digits
    for (int i = 0; i < 10; i++) {
        usedDigit[i] = false;
    }
    backtrack(0);

    if (!solutionFound) {
        printf("UNSOLVABLE\n");
        return 0;
    }

    // Sort the solutions lexicographically
    for (int i = 0; i < solutionCount - 1; i++) {
        for (int j = i + 1; j < solutionCount; j++) {
            if (strcmp(solutions[i], solutions[j]) > 0) {
                char temp[300];
                strcpy(temp, solutions[i]);
                strcpy(solutions[i], solutions[j]);
                strcpy(solutions[j], temp);
            }
        }
    }

    // Print
    for (int i = 0; i < solutionCount; i++) {
        printf("%s\n", solutions[i]);
    }

    return 0;
}
