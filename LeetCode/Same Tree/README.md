# Same Tree

Problem: [LeetCode](https://leetcode.com/problems/same-tree/description/)

Given the roots of two binary trees `p` and `q`, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Example 1:

![example1](ex1.jpg)

Input: $p = [1,2,3]$, $q = [1,2,3]$  
Output: $true$

Example 2:

![example2](ex2.jpg)

Input: $p = [1,2]$, $q = [1,null,2]$  
Output: $false$

Example 3:

![example3](ex3.jpg)

Input: p = $[1,2,1]$, $q = [1,1,2]$  
Output: $false$


## Solution
We are told that the number of nodes in both trees is in the range $\in [0, 100]$ and that $-10^{4} \le \text{Node.val} \le 10^{4}$.

We are also given the definition of a **binary tree node**:

```cpp
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 ```

Given the root nodes `p` and `q` of two binary trees, we can implement a *recursive* algorithm to verify if they are the same.  
The two trees are the same if they are **structurally identical**.

We can check this by recursively checking both trees, starting from their **root nodes**: 

 - if `p` and `q` are both `nullptr`, then they are the same, so we return `true`.
 - if one of them is `nullptr` but the other isn't, then they are not the same, so we return `false`.
 - if they differ in value, they are not the same, so we return `false`
 - we continue this process by recursively checking if both **left subtrees** are the same and also if both **right subtrees** are the same.

#### Pseudocode

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {

    // if both are nullptr, they are the same
    if (p == nullptr && q == nullptr) {
        return true;
    }

    // if one is nullptr but the other isn't, they are not the same
    else if (p == nullptr || q == nullptr) {
        return false;
    }
    
    // if they differ in value, they are not the same
    else if (p->val != q->val) {
        return false;
    }

    // recursively check they have the same left and right subtrees
    else {
        return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
    }
}
```

#### Complexity
The algorithm visits each node at least once. Assuming there are $n$ nodes in both trees, the total **time complexity** is $\Theta(n)$.

The total **space complexity** is given by the extra memory allocated on the stack due to the recursive calls, which depends on the height $h$ of the tree(s), leading to a cost of $\Theta(h)$. In the worst case, this means $\Theta(n)$, while in the best case, such as a *complete tree*, this means $\Theta(\log n)$.
