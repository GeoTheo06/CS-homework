#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string pattern, text;

	while (true) {
		if (!getline(cin, pattern)) {
			break;
		}
		if (!getline(cin, text)) {
			break;
		}

		vector<int> occurrences;
		int n = text.size(), m = pattern.size();
		for (int i = 0; i + m <= n; i++) {
			if (text.compare(i, m, pattern) == 0) {
				occurrences.push_back(i);
			}
		}

		if (occurrences.size() == 0) {
			cout << "\n";
		} else {
			for (int i = 0; i < (int)occurrences.size(); i++) {
				if (i > 0) cout << " ";
				cout << occurrences[i];
			}
			cout << "\n";
		}
	}

	return 0;
}
