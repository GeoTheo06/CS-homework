#include <stdio.h>
#include <stdlib.h>

int *copySubArray(int left, int right, int arr[]) {
  int *copy = malloc((right - left)*sizeof(int));
  for (int i=left; i < right; i++) {
    copy[i - left] = arr[i];
  }
  return copy;
}

void mergeSort(int length, int arr[]) {
  if (length <= 1) {
    return;
  }

  int mid = length/2;
  int *left = copySubArray(0, mid, arr);
  int *right = copySubArray(mid, length, arr);

  mergeSort(mid, left);
  mergeSort(length - mid, right);

  int idx = 0;
  int l = 0;
  int r = 0;
  while ((l < mid) && (r < length - mid)) {
    if (left[l] < right[r]) {
      arr[idx] = left[l];
      l++;
    } else {
      arr[idx] = right[r];
      r++;
    }
    idx++;
  }
  while (l < mid) {
    arr[idx] = left[l];
    idx++;
    l++;
  }
  while (r < length - mid) {
    arr[idx] = right[r];
    idx++;
    r++;
  }
  free(left);
  free(right);
}

int main() {
    int n;
    scanf("%d:", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    mergeSort(n, arr);

    int max = 0;
    int minPtr = 0;
    int currMinPtr = 0;
    int maxPtr = 0;
    int count = 0;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i + 1] - arr[i] <= 1) {
            count++;
        } else {
            int current = count + 1;
            if (current > max || (current == max && arr[currMinPtr] < arr[minPtr])) {
                max = current;
                minPtr = currMinPtr;
                maxPtr = i;
            }
            currMinPtr = i + 1;
            count = 0;
        }
    }

    // Process the last sequence
    int current = count + 1;
    if (current > max || (current == max && arr[currMinPtr] < arr[minPtr])) {
        max = current;
        minPtr = currMinPtr;
        maxPtr = n - 1;
    }

    printf("%d:[%d,%d)\n", max, arr[minPtr], arr[maxPtr] + 1);
    free(arr);
    return 0;
}