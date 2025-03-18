#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
	long long n, d;
	cin >> n >> d;
	vector<long long> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	unordered_map<long long, long long> freq;

	for (int i = 0; i < n; i++) {
		long long q = arr[i] / d;
		freq[q]++;
	}

	long long res = 0;
	for (auto &i : freq) {
		long long count = i.second;
		res += (count * (count - 1)) / 2;
	}

	cout << res << endl;
	return 0;
}
