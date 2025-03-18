#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (n--) {
		string line;
		getline(cin, line);
		vector<long long> digs;
		{
			stringstream ss(line);
			while (ss.good()) {
				string str;
				getline(ss, str, ',');

				if (str.empty()) {
					digs.push_back(0);
				} else {
					digs.push_back(stoll(str));
				}
			}
		}
		long long result = 0;
		for (auto d : digs) {
			result = result * 60 + d;
		}

		cout << result << "\n";
	}

	return 0;
}
