#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(nullptr);
	static double C[501][501];

	int n, k;
	cin >> n >> k;

	vector<double> s(n + 1, 0.0);
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}

	// Precompute combinations C(i, r)
	for (int i = 0; i <= n; i++) {
		C[i][0] = 1.0;
		for (int r = 1; r <= i; r++) {
			C[i][r] = C[i - 1][r - 1] + C[i - 1][r];
		}
	}

	double total_comb = C[n][k];

	for (int i = 1; i <= n; i++) {
		s[i] /= 100.0;
	}

	vector<double> result(n + 1, 0.0);

	// Every chosen monster gets its own share
	for (int i = 1; i <= n; i++) {
		result[i] += s[i] * (double)k / (double)n;
	}

	// handling the extra contributions from non-chosen monsters
	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++) {
			if (i == j) continue;

			double p_next = 0.0;
			if (i > j) {
				// i is after j in the list
				int diff = i - j;
				p_next = C[n - diff][k - 1] / total_comb;
			} else {
				// i is before j, so wrap-around scenario
				int diff = j - i;
				p_next = C[diff][k - 1] / total_comb;
			}
			result[i] += s[j] * p_next;
		}
	}

	for (int i = 1; i <= n; i++) {
		result[i] *= 100.0;
	}

	cout << fixed << setprecision(6);
	for (int i = 1; i <= n; i++) {
		cout << result[i] << (i == n ? '\n' : ' ');
	}

	return 0;
}
