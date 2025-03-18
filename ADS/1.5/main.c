#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LibList.h"

int main(int argc, char *argv[]) {

  int size;
  if (!scanf("%d", &size)) {
    printf("input not scanned correctly\n");
  }

  int arr[size];
  for(int idx = 0; idx < size; ++idx) {
    if (!scanf("%d", &arr[idx])) {
      printf("input not scanned correctly\n");
    }
  }

  int pos;
  if (!scanf("%d", &pos)) {
    printf("input not scanned correctly\n");
  }

  List li = makeList(arr, size);
  printList(visitList, li, "original list is: ");
  printf("item at position %d is %d\n", pos, itemAtPosIt(li, pos));

  freeList(li);
}
