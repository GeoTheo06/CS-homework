#include "LibList.h"

int itemAtPosIt(List li, int p) {
  for (int i = 0; i < p; i++)
  {
	li = li->next;
	return li->item;
  }
  
}