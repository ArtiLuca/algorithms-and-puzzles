# Convert Sorted Array to Binary Search Tree

Problem: [LeetCode](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/)

Given an integer array `nums` where the elements are sorted in **ascending order**, convert it to a *height-balanced binary search tree*.

Example 1:

![btree1](btree1.jpg)

Input: nums = $[-10,-3,0,5,9]$  
Output: $[0,-3,9,-10,null,5]$  
Explanation: $[0,-10,5,null,-3,null,9]$ is also accepted:

![btree2](btree2.jpg)

Example 2:

![btree3](btree3.jpg)

Input: nums = $[1,3]$  
Output: $[3,1]$  
Explanation: $[1,null,3]$ and $[3,1]$ are both height-balanced BSTs.

## Solution

We are told that $1 \le \text{nums.length} \le 10^{4}$, $ \ -10^{4} \le \text{nums[i]} \le 10^{4}$, and that `nums` is sorted in a **strictly increasing order**.

We are also given the definition for a **binary tree node**:

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

If we want to obtain *height-balanced binary search tree* from an array of integers sorted in a increasing **strictly increasing order**, this means there are no *duplicates*. It also means, that to obtain the *most height-balanced* BST possible, we must use the middle element as the root.

That is, given $nums[0 \dots n]$, we want to use as the **root node** the element that is at the *middle* index  

$$
\lfloor \frac{n}{2} \rfloor
$$  

since this will produce the *most height-balanced* BST possible.  

We can take advantage of `nums` being sorted in increasing order to implement a *divide and conquer* approach.  
Assuming $nums[p \dots r]$ is a subarray of $nums[0 \dots n]$ and therefore smaller in size, we can implement `sortedArrayToBST` by implementing a *recursive helper procedure* `arrayToBSTrec(vector<int>nums&, int p, int r)` which allocates the node `x` at the *centre* of the interval $[p,r]$, which to avoid *overflow* is equivalent to $q = p + \frac{r - p}{2}$. We use as a base case $p > r$, in which case we simply return `nullptr`. The procedure then *recursively* calls `arrayToBSTrec(nums,p,q-1)` to allocate the **left subtree** and calls `arrayToBSTrec(nums,q+1,r)` to allocate the **right subtree**, before returning a pointer to the **root node** `x` of the newly allocated subtree.

We can then have `sortedArrayToBST(vector<int>& nums)` act as a *wrapper* function that calls `arrayToBSTrec(nums, 0, nums.size() - 1)`, which builds the *height-balanced* tree from the sorted array `nums` returning a pointer to the **root node** of the BST created.

#### Pseudocode

```cpp
// recursive helper procedur
TreeNode* arrayToBSTrec(vector<int>& nums, int p, int r) {

    // base case
    if (p > r) {
        return nullptr;
    }
    
    // equivalent to floor, but safer to avoid overflow
    int q = p + (r - p) / 2;
    TreeNode* x = new TreeNode(nums[q]);

    // allocate left subtree
    x->left = arrayToBSTrec(nums, p, q-1);

    // allocate right subtree
    x->right = arrayToBSTrec(nums, q+1, r);

    // return pointer to root of subtree
    return x;
}

// main function "wrapper"
TreeNode* sortedArrayToBST(vector<int>& nums) {

    return arrayToBSTrec(nums, 0, nums.size() - 1);
}
```

#### Complexity
If $n$ is totla number of elements in `nums`, assuming a constant amount of work per node $\Theta(1)$, the total **time complexity** is linear with the number of elements $n$, leading to $\Theta(n)$.

This can also be shown using the master theorem and the recurrence $T(n) = 2T(\frac{n}{2}) + \Theta(1)$.  
The *watershed function* is $n^{\log_{b}{a}} = n^{\log_{2}{2}} = n^1 = n$, which "dominates" over the constant work per node.  
This means **master theorem case 1** can be applied, as the only condition that $\exists \varepsilon > 0$ such that:  

$$
f(n) = \mathcal{O}(n^{{\log_{2}{2} + \varepsilon}})
$$ 

is verified for any $0 < \varepsilon < 1$, letting us conclude that:  
$T(n) = \Theta(n^{\log_{b}{a}}) = \Theta(n)$.

The total **time complexity** is givien by maximum depth of the runtime recursion call stack, which is strictly bounded by the maximum height of the tree, which is $\lfloor \log_2 n \rfloor$. 

**Note**: if we take into account the memory required to store the output tree itself, the total space complexity is $\mathcal{O}(n)$, but the helper memory stack takes only $\mathcal{O}(\log n)$.

