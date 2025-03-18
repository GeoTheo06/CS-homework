
#include <iostream>
#include <vector>
using namespace std;

vector<int> swap(vector<int> arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
	return arr;
}

int partition(vector<int> &arr, int start, int end) {
	int pivot = end;
	int big = 0;
	int small = end - 1;  //-1 to exclude the pivot (because pivot = end)
	while (small > big) {
		if (arr[small] < arr[pivot] && arr[big] > arr[pivot]) {
			arr = swap(arr, small, big);
		}

		if (arr[small] >= arr[pivot]) {
			small--;
		}
		if (arr[big] <= arr[pivot]) {
			big++;
		}
	}
	arr = swap(arr, big, pivot);
	return big;
}

void quickSort(vector<int> &arr, int start, int end) {
	if (start < end) {
		int pivot = partition(arr, start, end);
		quickSort(arr, start, pivot - 1);
		quickSort(arr, pivot + 1, end);
	}
}

int main() {
	vector<int> arr = {20, 10, 80, 50, 70, 30};
	quickSort(arr, 0, arr.size() - 1);
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << "\n";
	}
}