#include <iostream>
using namespace std;
/*
any valid N (N is guaranteed by the problem to be expressible as at least two composite numbers) can always be written as a sum of exactly two composite numbers.
if N is even then I can use 4 + N - 4, as N >= 8
if odd then 9 + N - 9 as N>=13
The problem guarantees there is a solution for the input N, so cases like N=9 where no such sum of two composites exists are fine
*/
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long N;
	cin >> N;

	cout << 2 << "\n";

	if (N % 2 == 0) {
		cout << 4 << " " << (N - 4) << "\n";
	} else {
		cout << 9 << " " << (N - 9) << "\n";
	}

	return 0;
}
