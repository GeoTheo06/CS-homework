#include "LibList.h"

List makeList(int arr[], int size) {

  List li = newEmptyList();

  for (int idx = 0; idx < size; ++idx)
    li = addItem(arr[idx], li);

  return li;
}