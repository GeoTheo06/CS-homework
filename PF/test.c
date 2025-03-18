#include <stdio.h>
#include <stdlib.h>

// Driver Code
int main(void) {
    for (int i = 0; i < 55; i++) {
        printf("%d,", rand() % 100);
    }

    printf("\n");
}