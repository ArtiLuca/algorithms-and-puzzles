# Search in a Binary Search Tree

Problem: [LeetCode](https://leetcode.com/problems/search-in-a-binary-search-tree/description/)

You are given the 'root' of a binary search tree (**BST**) and an integer 'val'.

Find the node in the BST that the node's value equals 'val' and return the **subtree** rooted with that node.  
If such a node does not exist, return 'null'.

Example:

![bst](bst.jpg)

In the image above, for example:

   Example 1
 - Input: $root = [4,2,7,1,3], val = 2$
 - Output: $[2,1,3]$

   Example 2
 - Input: $root = [4,2,7,1,3], val = 5$
 - Output: $[]$

## Solution

We are given the definition of a binary tree node:

```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 ```

We also know that the number of nodes in the tree is in the range $\in [1, 5000]$,  
$1 \le \text{Node.val} \le 10^{7}$, `root` is a **binary search tree**, and that $1 \le \text{val} \le 10^{7}$.

We can use the properties of a **BST** to search for the value `val`.  
We continue searching until we either find the node containing `val` as it's value or we reach a node that is `nullptr`.  
We use a pointer `curr` to the current node and start at the **root** of the tree. We then compare the value `val` being searched with the value of the current node.

 - if `val < curr.val` we then move the search to the **left subtree**.
 - otherwise, we move the search to the **right subtree**.

Once we exit this loop, if the search was successful we return the current node `curr` which contains `val` as its value  
and is the root of the subtree $(curr, curr.left, curr.right)$ where `curr.left` and `curr.right` could possibly be `nullptr`.  
If the search was not successful, then `curr` is `nullptr` so it is the root of an empty subtree.

We can implement the search using both a *recursive* and *iterative* approach. I opted for latter, to not use extra memory on the stack.

#### Pseudocode

```cpp
TreeNode* searchBST(TreeNode* root, int val) {

    TreeNode* curr = root;
    while (curr != nullptr && curr->val != val) {

        // move to left subtree
        if (val < curr->val) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    // root of node with value searched (empty if value was not found)
    return curr;
}
```

#### Complexity
Assuming the tree contains $n$ nodes, the total **time complexity** depends on the height $h$ of the tree.  
In the worst case $h=n$ and therfore we have $\mathcal{O}(n)$, while in the best case such as a *complete tree*  
we have $\mathcal{O}(\log n)$.  
In general though, the **time complexity** for the search operation is $\mathcal{O}(h)$.

Since we used an *iterative* approach, the total **space complexity** remains constant $\mathcal{O}(1)$.
