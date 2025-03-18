#include <math.h>

#include <algorithm>
#include <iostream>
using namespace std;
int main() {
	int n, m, k;
	cin >> n >> m >> k;
	int *applicants = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> applicants[i];
	}
	int *apartments = new int[m];
	for (int i = 0; i < m; i++) {
		cin >> apartments[i];
	}
	sort(applicants, applicants + n);
	sort(apartments, apartments + m);
	int j = 0, i = 0, prevApplic, firstTime = 1, counter = 0;
	while (i < m && j < n) {
		if (applicants[j] - k <= apartments[i] && applicants[j] + k >= apartments[i]) {
			counter++;
			i++;
			j++;
		}
		if (applicants[j] + k < apartments[i]) {
			j++;
		}
		if (applicants[j] - k > apartments[i]) {
			i++;
		}
	}
	cout << counter << endl;
}