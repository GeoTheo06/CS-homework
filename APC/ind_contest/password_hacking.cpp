#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<pair<string, double>> passwords;
	passwords.reserve(n);
	for (int i = 0; i < n; i++) {
		string pass;
		double p;
		cin >> pass >> p;
		passwords.push_back({pass, p});
	}

	sort(passwords.begin(), passwords.end(), [](auto &a, auto &b) {
		return a.second > b.second;
	});

	double temp = 0;
	for (int i = 0; i < n; i++) {
		temp += (i + 1) * passwords[i].second;
	}

	cout << fixed << setprecision(4) << temp << "\n";

	return 0;
}
