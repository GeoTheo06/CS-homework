/*

Your task is to find a minimum-price flight route from Syrjälä to Metsälä. You have one discount coupon, using which you can halve the price of any single flight during the route. However, you can only use the coupon once.
When you use the discount coupon for a flight whose price is x, its price becomes \lfloor x/2 \rfloor (it is rounded down to an integer).
Input
The first input line has two integers n and m: the number of cities and flight connections. The cities are numbered 1,2,\ldots,n. City 1 is Syrjälä, and city n is Metsälä.
After this there are m lines describing the flights. Each line has three integers a, b, and c: a flight begins at city a, ends at city b, and its price is c. Each flight is unidirectional.
You can assume that it is always possible to get from Syrjälä to Metsälä.
Output
Print one integer: the price of the cheapest route from Syrjälä to Metsälä.
Constraints

2 \le n \le 10^5
1 \le m \le 2 \cdot 10^5
1 \le a,b \le n
1 \le c \le 10^9

Example
Input:
3 4
1 2 3
2 3 1
1 3 7
2 1 5

Output:
2
*/

// my code works for most inputs. it is not dijstra but something similar. I know the issue is that i need to properly use priority queue probably, im a first year i will learn how to use it in c++ next week. if the problem is something else let me know.

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	int a, b;
	long long c;

	vector<vector<vector<long long>>> gr;

	for (int i = 0; i < n; i++) {
		gr.push_back(vector<vector<long long>>());
	}
	vector<long long> temp;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		gr[a - 1].push_back({b - 1, c});
	}

	vector<long long> costsUnused;
	vector<long long> costsUsed;

	for (int i = 0; i < n; i++) {
		costsUnused.push_back(-1);
		costsUsed.push_back(-1);
	}
	costsUnused[0] = 0;
	costsUsed[0] = 0;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < gr[i].size(); j++) {
			int destination = gr[i][j][0];
			long long cost = gr[i][j][1];

			// Update costsUnused if the path to this destination without using the coupon is cheaper
			if (costsUnused[destination] == -1 || costsUnused[i] + cost < costsUnused[destination]) {
				costsUnused[destination] = costsUnused[i] + cost;
			}

			// Update costsUsed by using the coupon on this edge if it hasn't been used yet
			if (costsUsed[destination] == -1 || costsUnused[i] + (cost / 2) < costsUsed[destination]) {
				costsUsed[destination] = costsUnused[i] + (cost / 2);
			}
			if (costsUsed[destination] == -1 || costsUsed[i] + cost < costsUsed[destination]) {
				costsUsed[destination] = costsUsed[i] + cost;
			}
		}
	}
	cout << costsUsed[costsUsed.size() - 1] << "\n";
}