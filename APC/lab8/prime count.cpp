// i found the sieve of eratosthenes online

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<bool> isPrime(n + 1, true);
	if (n >= 0) {
		isPrime[0] = false;
	}
	if (n >= 1) {
		isPrime[1] = false;
	}

	// Sieve of Eratosthenes
	for (int i = 2; i * i <= n; i++) {
		if (isPrime[i]) {
			for (int j = i * i; j <= n; j += i)
				isPrime[j] = false;
		}
	}

	int count = 0;
	for (int i = 2; i <= n; i++) {
		if (isPrime[i]) {
			count++;
		}
	}

	cout << count;
	return 0;
}