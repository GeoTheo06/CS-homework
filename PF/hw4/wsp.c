/* file: wsp.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Oct 03 2024 */
/* version: 1.0 */

/* Description:  This program reads a word game (2d plane of capital characters), reads some words that there are in the grid and outputs the letters in the grid that are not included in any of the words*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkWord(char tempWord[21], char word[21], char reverse[21], int numOfLetters) {
    // check if normal word is found in the specific places we searched for in this iteration in the grid
    bool found = true;
    for (int j = 0; j < numOfLetters; j++) {
        if (tempWord[j] != word[j]) {
            found = false;
            break;
        }
    }
    // checking for the reverse word
    bool rFound = true;
    for (int j = 0; j < numOfLetters; j++) {
        if (tempWord[j] != reverse[j]) {
            rFound = false;
            break;
        }
    }
    if (rFound || found) {
        return true;
    }
    return false;
}

void checkHorizontal(int numOfLetters, char word[21], char reverse[21], int n, char markedLetters[21][21], char grid[21][21]) {
    bool found;
    char tempWord[21];

    // runs for every element in the grid (as long as the length of the word and the initial position are in bounds)
    //   runs for rows
    for (int i = 0; i < n; i++) {
        // runs for columns
        for (int k = 0; k <= n - numOfLetters; k++) {
            // finding the possible word in the grid (it makes a possible word that has as many characters as there are in the current word)
            for (int j = k; j < k + numOfLetters; j++) {
                // j-k = 0 in the beginning and increments by one in each loop obviously
                tempWord[j - k] = grid[i][j];
            }

            found = checkWord(tempWord, word, reverse, numOfLetters);

            if (found) {
                for (int j = k; j < k + numOfLetters; j++) {
                    markedLetters[i][j] = '0';
                }
            }
        }
    }
}

void checkVertical(int numOfLetters, char word[21], char reverse[21], int n, char markedLetters[21][21], char grid[21][21]) {
    bool found;
    char tempWord[21];
    // runs for every element in the grid (as long as the length of the word and the initial position are in bounds)
    //   runs for columns
    for (int k = 0; k < n; k++) {
        // runs for rows
        for (int i = 0; i <= n - numOfLetters; i++) {
            for (int j = i; j < i + numOfLetters; j++) {
                tempWord[j - i] = grid[j][k];
            }

            found = checkWord(tempWord, word, reverse, numOfLetters);

            if (found) {
                for (int j = i; j < i + numOfLetters; j++) {
                    markedLetters[j][k] = '0';
                }
            }
        }
    }
}

void checkDiagonalUpToDown(int numOfLetters, char word[21], char reverse[21], int n, char markedLetters[21][21], char grid[21][21]) {
    bool found;
    char tempWord[21];
    int counter;
    // runs for every element in the grid (as long as the length of the word and the initial position are in bounds)
    for (int i = 0; i <= n - numOfLetters + 1; i++) {
        for (int k = 0; k <= n - numOfLetters + 1; k++) {
            // incrementing both rows and columns
            counter = i;
            for (int j = k; j < k + numOfLetters; j++) {
                tempWord[j - k] = grid[counter][j];
                counter++;
            }

            found = checkWord(tempWord, word, reverse, numOfLetters);

            if (found) {
                counter = i;
                for (int j = k; j < k + numOfLetters; j++) {
                    markedLetters[counter][j] = '0';
                    counter++;
                }
            }
        }
    }
}

void checkDiagonalDownToUp(int numOfLetters, char word[21], char reverse[21], int n, char markedLetters[21][21], char grid[21][21]) {
    bool found;
    char tempWord[21];
    int counter;
    // runs for every element in the grid (as long as the length of the word and the initial position are in bounds)
    for (int i = numOfLetters - 1; i < n; i++) {
        for (int k = 0; k < n - (numOfLetters - 1); k++) {
            // decrementing rows and incrementing columns
            counter = i;
            for (int j = k; j < k + numOfLetters; j++) {
                tempWord[j - k] = grid[counter][j];
                counter--;
            }

            found = checkWord(tempWord, word, reverse, numOfLetters);

            if (found) {
                counter = i;
                for (int j = k; j < k + numOfLetters; j++) {
                    markedLetters[counter][j] = '0';
                    counter--;
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    char grid[21][21], markedLetters[21][21];

    for (int i = 0; i < n; i++) {
        // read input
        scanf("%s", grid[i]);
    }

    // if letters[i][k] is 0 then the letter in the position i,k is not in the solution, else if its 1 then it is
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            // initialize letters array that works based on the actual grid
            markedLetters[i][k] = '1';
        }
    }

    // 20+1 because i put 0 after the word to know where it ends
    char word[21], reverse[21];
    int numOfLetters;

    scanf("%s", word);
    // putting 0 after the word.
    strcat(word, "0");

    while (word[0] != '.') {
        // counting how many letters the word has
        numOfLetters = 0;
        while (word[numOfLetters] != '0') {
            numOfLetters++;
        }

        // reversing word
        for (int i = 0; i <= numOfLetters; i++) {
            reverse[i] = word[numOfLetters - i - 1];
        }
        strcat(reverse, "0");

        checkHorizontal(numOfLetters, word, reverse, n, markedLetters, grid);
        checkVertical(numOfLetters, word, reverse, n, markedLetters, grid);
        checkDiagonalUpToDown(numOfLetters, word, reverse, n, markedLetters, grid);
        checkDiagonalDownToUp(numOfLetters, word, reverse, n, markedLetters, grid);

        scanf("%s", word);
        strcat(word, "0");
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (markedLetters[i][k] == '1') {
                printf("%c", grid[i][k]);
            }
        }
    }
    printf("\n");
}