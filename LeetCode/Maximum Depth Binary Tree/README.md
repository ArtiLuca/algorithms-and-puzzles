# Maximum Depth of Binary Tree

Problem: [LeetCode](https://leetcode.com/problems/maximum-depth-of-binary-tree/description/)

Given the `root` of a binary tree, return its *maximum depth*.

A binary tree's **maximum depth** is the number of nodes along the longest path from the root node down to the farthest leaf node.

Example:

![binary_tree_tmp](tmp_tree.jpg)

Example 1
- Input: root = [3,9,20,null,null,15,7]
- Output: 3

Example 2:
- Input: root = [1,null,2]
- Output: 2

## Solution
We are told that the number of nodes in the tree is in the range $\in [0, 10^{4}]$ and that $-100 \le \text{Node.val} \le 100$.

As in similar exercises, we are given the definition of a binary tree node:

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

The *depth* of a binary tree is the number of nodes found going from the **root node** to any **leaf node**.  
We want to find the **maximum depth**, meaning the longest path $\text{root} \to \text{leaf}$.

We can do this using a *recursive* approach, assuming as the base case that, if `root == nullptr`, the safe choice is to return `0`.   
Otherwise, we recursively find the depth of the **left subtree** `leftHeight` and the depth of the **right subtree** `rightHeight`.  

We then take the maximum found by the recursive calls and add $+1$ to update the **maximum depth** to also count the current level:

$$
\text{return }
\max(\text{leftHeight}, \text{rightHeight})
+1
$$

#### Pseudocode

```cpp
int maxDepth(TreeNode* root) {

      // base case
      if (root == nullptr) {
          return 0;
      }

      int leftHeight = maxDepth(root->left);
      int rightHeight = maxDepth(root->right);

      // update maximum depth
      return max(leftHeight, rightHeight) + 1;
}
```

#### Complexity
Intuitively, if $n$ is the number of nodes in the binary tree, the total **time complexity** is $\Theta(n)$ since we visit each node.

We can also see this by taking a generic subtree rooted at node `x`. Assuming it's left subtree contains $k$ nodes,  
and that it's right subtree contains $n-k-1$ nodes, we can express the complexity using the recurrence:

$T(n) = T(k) + T(n-k-1) + \Theta(1)$

where $\Theta(1)$ is the constant work done at each step.  
The above recurrence can be simplified to $\Theta(n)$, which can be proven by substitution.  

The **space complexity** is $\mathcal{O}(h)$ due to the extra memory allocated onto the stack by the recursive calls.
