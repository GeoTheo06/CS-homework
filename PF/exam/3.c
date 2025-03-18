
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d:", &n);

    int *in = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }

        int arr[101];

    for (int i = 0; i <= 100; i++) {
        arr[i] = 0;
    }

    arr[0] = n;

    int max = 0;

    max = in[0];

    int sum = 0;

    int index = 0;
    int temp;
    int countOnes = 0;
    int numBeforeOne = 0;
    while (countOnes < index + 1) {
        sum = 0;

        countOnes = 0;

        // counts ones and makes 0 the places with 1s.
        for (int i = 0; i <= index; i++) {
            if (arr[i] == 1) {
                countOnes++;
                arr[i] = 0;
            }
        }

        numBeforeOne = index - countOnes;

        arr[numBeforeOne]--;

        int numbersThatNeedPutting = countOnes + 1;
        temp = numBeforeOne + 1;
        while (numbersThatNeedPutting >= arr[numBeforeOne]) {
            arr[temp] = arr[numBeforeOne];
            numbersThatNeedPutting -= arr[numBeforeOne];
            temp++;
        }
        // in the end put whatever's left.
        arr[temp] = numbersThatNeedPutting;

        temp = 0;
        countOnes = 0;
        while (temp <= 100 && arr[temp] != 0) {
            sum += in[arr[temp]-1];

            if (arr[temp] == 1) {
                countOnes++;
            }

            temp++;
        }
        index = temp - 1;
		
		if(sum > max){
            max = sum;
        }
    }

    printf("%d\n", max);

    return 0;
}