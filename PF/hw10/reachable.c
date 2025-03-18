/* file: reachable.c */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Wed Nov 04 2024 */
/* version: 1.0 */

/* Description: This program checks if you can reach the end of the array by jumping positions. Each number in the list tells you how far you can jump from that index. It uses recursion to try all possible jumps and prints "YES" if you can reach the end, or "NO" if you can't.*/

#include <stdio.h>
#include <stdlib.h>
int jump(int arr[], int index, int size, int dp[]) {
    // base case
    if (index >= size) {
        return 1;
    }
    if (arr[index] == 0) {  // cannot move further so backtrack
        dp[index] = 0;
        return 0;
    }
    if (dp[index] == 0) {
        return 0;
    }

    // recursive case. for each index it will travel all possible positions
    for (int i = 1; i <= arr[index]; i++) {
        // if it returned 1 then we have reached the end and can empty the stack by returning 1
        if (jump(arr, i + index, size, dp)) {
            return 1;
        }
    }
    // exhausted all possible combinations
    dp[index] = 0;
    return 0;
}

int main() {
    int num;
    scanf("%d", &num);
    int *arr = (int *)malloc(num * sizeof(int));
    int temp;
    for (int i = 0; i < num; i++) {
        scanf("%d", &temp);
        arr[i] = temp;
    }

    int *dp = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < num; i++) {
        dp[i] = -1;
    }

    // num - 1 because i will compare the size to index
    if (jump(arr, 0, num - 1, dp)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    free(arr);
    free(dp);
    return 0;
}
