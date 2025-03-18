#include <iostream>
#include <set>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	multiset<int> tickets;
	int temp;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		tickets.insert(temp);
	}

	int maxPr;
	for (int i = 0; i < m; ++i) {
		cin >> maxPr;
		auto it = tickets.upper_bound(maxPr);
		if (it == tickets.begin()) {
			cout << -1 << endl;
		} else {
			it--;
			cout << *it << endl;
			tickets.erase(it);
		}
	}

	return 0;
}
