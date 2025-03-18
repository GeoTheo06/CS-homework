#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	char ch = '0';
	vector<vector<char>> in;
	int count = 0;
	char chPrev = '0';
	for (int i = 0; i < n; i++) {
		in.push_back({});
		for (int j = 0; j < m; j++) {
			chPrev = ch;

			if (j == 0) { // different star because from left
				chPrev = '0';
			}

			cin >> ch;
			in[i].push_back(ch);

			if (ch == '#') {
			// reset:

			}

			if (chPrev != '-') {
				if (ch == '-') {
					count++;
				}
			}


		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << in[i][j];
		}
		cout << endl;
	}
}