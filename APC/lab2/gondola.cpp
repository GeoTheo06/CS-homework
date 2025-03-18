#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	int n, x;
	cin >> n >> x;
	vector<int> weights;
	int temp;

	for (int i = 0; i < n; i++) {
		cin >> temp;
		weights.push_back(temp);
	}

	sort(weights.begin(), weights.end());
	int counter = 0, alone = 0;
	int k = n - 1;
	int i = 0;
	while (i < k) {
		if (weights[i] + weights[k] <= x) {
			counter++;
			i++;
			k--;
		} else {
			k--;
			alone++;
		}
	}
	if (i > k) {
		cout << counter + alone;
	} else {
		cout << counter + alone + 1;
	}
}