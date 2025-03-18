#include <iostream>
#include <vector>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	vector<int> count(a + b + 1, 0);

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			count[i + j]++;
		}
	}

	int max = 0;
	for (int i = 2; i <= a + b; i++) {
		if (count[i] > max) {
			max = count[i];
		}
	}

	for (int i = 2; i <= a + b; i++) {
		if (count[i] == max) {
			cout << i << "\n";
		}
	}

	return 0;
}
