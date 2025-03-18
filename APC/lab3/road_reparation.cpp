/*
There are n cities and m roads between them. Unfortunately, the condition of the roads is so poor that they cannot be used. Your task is to repair some of the roads so that there will be a decent route between any two cities.
For each road, you know its reparation cost, and you should find a solution where the total cost is as small as possible.
Input
The first input line has two integers n and m: the number of cities and roads. The cities are numbered 1,2,\dots,n.
Then, there are m lines describing the roads. Each line has three integers a, b and c: there is a road between cities a and b, and its reparation cost is c. All roads are two-way roads.
Every road is between two different cities, and there is at most one road between two cities.
Output
Print one integer: the minimum total reparation cost. However, if there are no solutions, print "IMPOSSIBLE".
Constraints

1 \le n \le 10^5
1 \le m \le 2 \cdot 10^5
1 \le a,b \le n
1 \le c \le 10^9

Example
Input:
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4

Output:
14
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<long long>> roads;

	int a, b;
	long long c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		roads.push_back({a - 1, b - 1, c});	 // node A, node B, Cost
	}

	sort(roads.begin(), roads.end(), [](vector<long long> a, vector<long long> b) {
		return a[2] < b[2];
	});

	vector<int> parents;
	vector<int> parentOfNode;  // will store the position of the parent in the parents array.

	for (int i = 0; i < n; i++) {
		parentOfNode.push_back(-1);
	}

	long long sum = 0;
	for (int i = 0; i < m; i++) {
		int nodeA = roads[i][0];
		int nodeB = roads[i][1];

		if (parentOfNode[nodeA] == -1 && parentOfNode[nodeB] == -1) {
			parents.push_back(nodeA);
			parentOfNode[nodeA] = parents.size() - 1;
			parentOfNode[nodeB] = parents.size() - 1;
			sum += roads[i][2];
		} else if (parentOfNode[nodeA] != -1 && parentOfNode[nodeB] != -1) {
			if (parents[parentOfNode[nodeB]] != parents[parentOfNode[nodeA]]) {
				for (int k = 0; k < parents.size(); k++) {
					if (parents[k] == parents[parentOfNode[nodeB]]) {
						parents[parentOfNode[nodeB]] = parents[parentOfNode[nodeA]];
					}
				}
				sum += roads[i][2];
			}
		} else if (parentOfNode[nodeA] != -1) {
			parentOfNode[nodeB] = parentOfNode[nodeA];
			sum += roads[i][2];
		} else {
			parentOfNode[nodeA] = parentOfNode[nodeB];
			sum += roads[i][2];
		}

		// if (roads[i][2] == 6) {
		// 	cout << "node" << nodeA + 1 << nodeB + 1;
		// 	cout << "parents: ";
		// 	for (int i = 0; i < parents.size(); i++) {
		// 		cout << parents[i] + 1 << " ";
		// 	}
		// 	cout << "parentOfNode:\n";
		// 	for (int i = 0; i < parentOfNode.size(); i++) {
		// 		cout << i + 1 << ": " << parentOfNode[i] << "\n";
		// 	}
		// }
	}
	int firstPar = parents[0];
	int isConnected = 1;
	for (int i = 0; i < parents.size(); i++) {
		if (firstPar != parents[i]) {
			isConnected = 0;
			cout << "IMPOSSIBLE\n";
		}
	}
	if (isConnected) {
		cout << sum << "\n";
	}
}