#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int* arr = new int[n - 1];
  for (int i = 0; i < n - 1; i++) {
    cin >> arr[i];
  }

  sort(arr, arr + n - 1);

  int missing = n;
  for (int i = 0; i < n - 1; i++) {
    if (arr[i] != i + 1) {
      missing = i + 1;
      break;
    }
  }
  cout << missing << endl;

  delete[] arr;
  return 0;
}
