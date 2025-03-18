/* file: dna.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Oct 09 2024 */
/* version: 1.0 */

/* Description: reads a DNA pattern, then reads some names and their DNA and outputs in which position the pattern was found in which people's DNAs if it was found. It also outputs the number of DNA matches that were found.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read a line efficiently
char *read_line() {
    size_t size = 1024;
    size_t len = 0;
    char *buffer = malloc(size);
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        buffer[len++] = c;
        if (len == size) {
            size *= 2;
            buffer = (int *)realloc(buffer, sizeof(int) * size);
        }
    }
    buffer[len] = '\0';
    return buffer;
}

int main() {
    // Read the pattern
    char *pattern = read_line();

    // Read the number of genomes
    int n;
    scanf("%d", &n);
    getchar();  // Consume the newline after the number

    int matches = 0;
    for (int i = 0; i < n; i++) {
        char *line = read_line();
        if (strlen(line) == 0) {
            free(line);
            continue;
        }

        // Split the line into name and genome
        char *colon = strchr(line, ':');
        if (!colon) {
            free(line);
            continue;
        }
        *colon = '\0';
        char *name = line;
        char *genome = colon + 1;

        // Remove any leading spaces in genome
        while (*genome == ' ') genome++;

        // Find the first occurrence of the substring pattern in the string genome
        char *pos = strstr(genome, pattern);
        if (pos != NULL) {
            matches++;
            int shift = pos - genome;
            printf("%s: shift=%d\n", name, shift);
        }

        free(line);
    }

    if (matches == 1) {
        printf("1 match found.\n");
    } else {
        printf("%d matches found.\n", matches);
    }

    free(pattern);
    return 0;
}
