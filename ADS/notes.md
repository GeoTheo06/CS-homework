! in compact tries, to create the indexing, you use the initial state (not the compressed state)
Go see example to make clearer

```
def DFS(graph, v, visited):
    visited.add(v)
    for neighbor in graph[v]:
        if neighbor not in visited:
            DFS(graph, neighbor, visited)
```

```
def BFS(graph, start):
    visited = set()
    queue = deque([start])
    visited.add(start)

	while queue:
        v = queue.dequeue()
        for neighbor in graph[v]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
```

"Suppose we apply BFS and DFS to the same simple connected graph. What do we know about the height of the two resulting spanning trees? Explain and justify your answer! In the BFS spanning tree each branch from the root to a leaf corresponds to a shortest path. Hence the height of the BFS spanning tree is lower than or equal to the height of the DFS spanning tree."

! in lists everything happens on the first node:
they implement addItem(item, list) by creating a node behind the node you give them (newNode->next = list) this means the node you give them has to be the first.
they implement removeItem by removing the node and returning the next one. this means the node you delete has to be the first one.

list->item, list->next are not considered internal

count recursively:
![[Pasted image 20250407123743.png]]


recursive grammar:
![[Pasted image 20250407142106.png]]

grammar: <> means variables, [] means optional, | means or, {} means loop
![[Pasted image 20250407142847.png]]

![[Pasted image 20250407181353.png]]
### euler graph
Euler path uses every bridge (edge) (not vertex!) exactly once. (so the start and end node have to have odd degree)

you can have at most two vertices of odd degree. (start at one and end at the other)
(Note that actually there doesn't exist a graph with 1 vertice of odd degree because the sum of the degrees has to be even)

Euler circuit: all vertices must have even degree (because you start and end at the same node).


Code of the data structures:
https://chatgpt.com/share/67c877bb-7b88-800b-a819-85708f62e771

### trees
a tree with n nodes has n-1 edges
sum of degrees = 2 * edges

**simple path**: all nodes are different (we don't go over the same nodes)
**simple cycle**: all nodes are different except begin and end (because its the same) and there have to be at least 3 
**simple graph**: when it contains no loops and no parallel edges

**spanning tree** of a graph: a subgraph with the nodes that make a tree

## Trees (but different?)

array representation of a node's parent (1-indexed):
```
int parent = index // 2; (and floor it)
```

complete binary tree: ![[Pasted image 20250304122215.png]]

**perfect tree**: When all leaves are on the same depth h. There are 1 + 2 + 4 + ...2^h = 2^(h+1) −1 nodes.


A perfect binary tree stores 2^(h+1) −1 objects, each reachable in at most h steps.

given height h, the number of nodes N is between O(h) and O(2^h).  
Conversely, given N nodes, the height h is between O(N ) and O(log(N))

**heap**: is always a complete binary tree and it supports duplicate values
search tree does not support duplicate values

### priority queue (with heap): 

Upheap: if parent bigger then swap
downheap: go to the biggest child

to restore heap order after inserting a number: imagine you put the number after the last node (after the last element in an array | next to the last child in a tree) then do upheap to restore heap.
![[Pasted image 20250305152232.png]]

to implement removeMax: remove and return the value in the root -> last node becomes root -> downheap to restore heap
![[Pasted image 20250305152220.png]]

the reason we make the last node root is because there is not a clear way to restore the heap after removing the root.

compressed trie has O(m) nodes where m is number of words (not letters!). This is because non leaves ≤ leaves=m (each  leaf defines the end of a word). Hence total nodes = O(2m)

compact trie: it's just a compressed trie but instead of letters it stores the location range in the array
![[Pasted image 20250305162448.png]]

deletes a node from a tree (when the node has 2 children then it doesnt matter if in place of the node you substitute the biggest node from the left subtree or the smallest node from the right subtree)
```
// Finds the minimum node in a BST (used for deletion).
Tree findMin(Tree t) {
    while (t->left != NULL)
        t = t->left;
    return t;
}

// Deletes an element from the BST.
// Again, average-case O(log n) but worst-case O(n).
Tree deleteBST(int n, Tree t) {
    if (t == NULL) return t;
    if (n < t->data)
        t->left = deleteBST(n, t->left);
    else if (n > t->data)
        t->right = deleteBST(n, t->right);
    else {  // Found node to delete.
        if (t->left == NULL) {
            Tree temp = t->right;
            free(t);
            return temp;
        } else if (t->right == NULL) {
            Tree temp = t->left;
            free(t);
            return temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in right subtree)
            Tree temp = findMin(t->right);
            t->data = temp->data;
            t->right = deleteBST(temp->data, t->right);
        }
    }
    return t;
}
```