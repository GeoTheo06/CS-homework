#include "LibList.h"

void printList(void (*print)(List li), List li, char *arr) {
  printf("%s", arr);
  print(li);
  printf("\n");
}