# Common Functions

### Sorting

-   Ascending:
    sort(v.begin(), v.end());
-   Descending:  
    sort(v.rbegin(), v.rend());
* to sort this: {1, 2, 5}, {3, 4, 1}, {6, 7, 3} based on the 3rd element of each subset:
```sort(vector.begin(), vector.end(), [](vector<int> a, vector<int> b) {
return a[2] < b[2];
});
```

### Searching

-   set/Map:
    auto it = container.find(t); // complexity: logn | t can be either value or iterator. Returns the first occurance of 't' or the value pointed by the iterator 't'

-   Vector:
    upper_bound(numbers.begin(), numbers.end(), t); // complexity: O(n)

### Removing

-   Set/Multiset/Map/Multimap:
    s.erase(t) // Complexity: logn | t can be either value or iterator. Returns the first occurance of 't' or the value pointed by the iterator 't'.

-   Vector:
    v.erase(v.begin() + 2); // Removes the element at index 2
    v.erase(v.begin(), v.begin() + 2); // Removes the first two elements

### Bounds in Sets/Maps:

-   container.upper_bound(t) // Complexity: logn | returns an iterator to the first element > t.
-   container.lower_bound(t) // returns an iterator to the first element >= t.

-   container.find(t) // for sets/maps | complexity: logn (O(1) for unordered set) | returns an iterator to the first occurrence of t.
    If not found, returns container.end()

### reversing

-   reverse(v.begin(), v.end());

### Iterators

-   s.begin() // gives first element position (iterator)
-   s.end() // gives one position AFTER last element (iterator)

# read character by character:

```
getchar();
```

# files input/output

```
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
```

# read line by line:

```
getline();
```

# Read unknown amount of data:

```
#include
<bits/stdc++.h>
using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); // process until end of input

	while (cin >> x)
	{
		// solution
	}
}
```

# To set decimal precision:

```
 #include <iomanip>
 cout << setprecision(2) << fixed;
```

OR

```
printf("%.2f\n", x);
```

# Compare floating point numbers:

```
abs(a-b) < 1e-9 //because there may be rounding errors.

For example: only "now they are" will be printed:
double a = 0.3 * 3 + 0.1;
	int b = 1;

	if (a == b) {
		cout << "they are";
	}
	if (abs(a - b) < 1e-9) {
		cout << "now they are";
	}
```

# DATA STRUCTURES:

-   Vector | Complexity: O(1) for insertions/deletions at the end & O(n) for searching & O(1) for indexing

-   Deque | Complexity: O(1) for insertions/deletions at both ends

-   Set, Multiset | Complexity: O(logn) for insertion/deletion/searching and O(n) indexing.

-   unordered_set, unordered_map | Complexity: O(1) for insertion/deletion/searching but no indexing

-   List | Complexity: O(1) for insertion/deletion when given the iterator & O(n) searching/indexing

-   Map | Complexity: O(log n) for inserting/deleting/indexing/searching

-   Unordered Maps | Complexity: average: O(1) and worst: O(n) (when collsion occurs) for inserting/deleting/indexing/searching.

### Note:

-   We use indices when working with containers like vector or arrays that support random access and provide constant-time access to elements.
-   We use iterators for containers like list, set, map, or even vector when you need flexibility in traversal and when you need to work with containers that don't support random access or contiguous memory. The values of iterators can be accessed with \*

## Vectors

-   when you need to do delete operations /sorting in a vector often, use sets/multisets instead. They are generally more efficient.
    
## Deque: vector but also has .push_front() and .push_front()

## set: sorts automatically (distinct) elements as they are inserted. There cannot be duplicate elements.

```
set<int> s;
s.insert(2);
s.insert(6);
s.insert(5);
s.insert(5);  // this does not do anything
s.erase(5);	  // removed the only 5 it finds
cout << s.count(5);	 // counts how many 5s exist. Returns either 0 or 1
s.upper_bound(t) // for sets/maps | Complexity: logn | returns an iterator to the first element > t.
s.lower_bound(t) // for sets/maps | returns an iterator to the first element >= t.
s.begin();	 // obviously returns 2 (the smallest number) because elements are sorted
s.find(6);	 // returns the iterator of value 6. If it doesn't exist, it will return s.end()
for (auto it = s.begin(); it != s.end(); ++it) {
	cout << *it; // prints the values of s
}
```

## Multiset: sorts automatically elements. Used for when there are duplicate elements.

```
multiset<int> s;
s.insert(5);
s.insert(5);
s.insert(5);
cout << s.count(5); // 3
auto it = s.find(5); // Returns iterator to the first occurrence of 5
s.erase(s.find(5));	 // only the first 5 will be removed
s.erase(5); // all occurrences of 5 are removed
cout << s.count(5); // 0
```

## Map: just an array but instead of indexing with increasing numbers (0,1,2) we index with any data type.

(Index is named "key" here)

```
map<string,int> m;
m["monkey"] = 4;
m["banana"] = 3;
m["harpsichord"] = 9;
cout << m["banana"] << "\n"; // 3
```

-   IMPORTANT: If the value of a key is requested but the map does not contain it, the key is automatically added to the map with a default value.For example, in the following code, the key ”aybabtu” with value 0 is added to the map.

```
map<string,int> m;
cout << m["aybabtu"] << "\n"; // 0
```

-   Check if key exists in a map with "count":

```
if (m.count("aybabtu")) {
// key exists
}
```

-   Get the key and the value of specific elements with ->first and ->second:

```
int main() {
	map<std::string, int> m;
	word_count["apple"] = 5;
	word_count["banana"] = 3;
	word_count["orange"] = 8;

	for (auto x : m) {
		cout << x.first << " " << x.second << "\n";
	}
}
```

## Lists

DO THIS

# TIME COMPLEXITY

## input size required time complexity

-   n is large O(1) or O(logn)

-   n ≤ 10^6 <=> O(nlogn) or O(n)

-   n ≤ 5000 <=> O(n^2)

-   n ≤ 500 <=> O(n^3)

-   n ≤ 20 <=> O(2^n)

-   n ≤ 10 <=> O(n!)

## The following list contains common time complexities of algorithms:

-   O(1) The running time of a constant-time algorithm does not depend on the input size. A typical constant-time algorithm is a direct formula that calculates the answer.

-   O(log n) A logarithmic algorithm often halves the input size at each step. The running time of such an algorithm is logarithmic, because log2(n) equals the number of times n must be divided by 2 to get 1.

-   O(sqrt(n)) A square root algorithm is slower than O(logn) but faster than O(n). A special property of square roots is that sqrt(n) = n/sqrt(n), so the square root sqrt(n) lies, in some sense, in the middle of the input.

-   O(n) A linear algorithm goes through the input a constant number of times. This is often the best possible time complexity, because it is usually necessary to access each input element at least once before reporting the answer.

-   O(nlogn) This time complexity often indicates that the algorithm sorts the input, because the time complexity of efficient sorting algorithms is O(nlogn). Another possibility is that the algorithm uses a data structure where each operation takes O(logn) time.

-   O(n^2) A quadratic algorithm often contains two nested loops. It is possible to go through all pairs of the input elements in O(n^2) time.

-   O(n^3) A cubic algorithm often contains three nested loops. It is possible to go through all triplets of the input elements in O(n^3) time.

-   O(2^n) This time complexity often indicates that the algorithm iterates through all subsets of the input elements.
    For example, the subsets of {1,2,3} are {1}, {2}, {3}, {1,2}, {1,3}, {2,3} and {1,2,3}.

-   O(n!) This time complexity often indicates that the algorithm iterates through all permutations of the input elements.
    For example, the permutations of {1,2,3} are (1,2,3), (1,3,2), (2,1,3), (2,3,1), (3,1,2) and (3,2,1).

# Algorithms

## Merge Sort

Complexity: O(nlogn) stable.

```
// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  // Use std::vector to dynamically allocate arrays
  vector<int> L(n1);
  vector<int> M(n2);

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];

  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i = 0, j = 0, k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

// Print the array
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

// Driver program
int main() {
  int arr[] = {6, 5, 12, 10, 9, 1};
  int size = sizeof(arr) / sizeof(arr[0]);
  mergeSort(arr, 0, size - 1);
  cout << "Sorted array: \n";
  printArray(arr, size);
  return 0;
}
```

## BFS

```
// C++ program for BFS of an undirected graph
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS from given source s
void bfs(vector<vector<int>>& adj, int s)
{
    // Create a queue for BFS
    queue<int> q;

    // Initially mark all the vertices as not visited
    // When we push a vertex into the q, we mark it as
    // visited
    vector<bool> visited(adj.size(), false);

    // Mark the source node as visited and
    // enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate over the queue
    while (!q.empty()) {

        // Dequeue a vertex from queue and print it
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        // Get all adjacent vertices of the dequeued
        // vertex curr If an adjacent has not been
        // visited, mark it visited and enqueue it
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(vector<vector<int>>& adj,
                          int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected Graph
}

int main()
{
    // Number of vertices in the graph
    int V = 5;

    // Adjacency list representation of the graph
    vector<vector<int>> adj(V);

    // Add edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    // Perform BFS traversal starting from vertex 0
    cout << "BFS starting from 0 : \n";
    bfs(adj, 0);

    return 0;
}
```

## DFS

```
void DFSRec(vector<vector<int>> &adj, vector<bool> &visited, int s){

    visited[s] = true;

    // Print the current vertex
    cout << s << " ";

    // Recursively visit all adjacent vertices
    // that are not visited yet
    for (int i : adj[s])
        if (visited[i] == false)
            DFSRec(adj, visited, i);

}

// Main DFS function that initializes the visited array
// and call DFSRec
void DFS(vector<vector<int>> &adj, int s){
vector<bool> visited(adj.size(), false);
DFSRec(adj, visited, s);
}

// To add an edge in an undirected graph
void addEdge(vector<vector<int>> &adj, int s, int t){
adj[s].push_back(t);
adj[t].push_back(s);
}

int main(){
int V = 5;
vector<vector<int>> adj(V);

    // Add edges
    vector<vector<int>> edges={{1, 2},{1, 0},{2, 0},{2, 3},{2, 4}};
    for (auto &e : edges)
        addEdge(adj, e[0], e[1]);

    int s = 1; // Starting vertex for DFS
    cout << "DFS from source: " << s << endl;
    DFS(adj, s); // Perform DFS starting from the source vertex

    return 0;

}
```

1
