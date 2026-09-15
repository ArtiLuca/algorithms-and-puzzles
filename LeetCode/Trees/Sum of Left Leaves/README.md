# Sum of Left Leaves

Problem: [LeetCode](https://leetcode.com/problems/sum-of-left-leaves/description/)

Given the `root` of a binary tree, return the *sum of all left leaves*.

A **leaf** is a node with no children. A **left leaf** is a leaf that is the left child of another node.

![leftSumTree](leftsum_tree.jpg)

Example 1:

Input: `root = [3,9,20,null,null,15,7]`  
Output: 24  
Explanation: There are two left leaves in the binary tree, with values 9 and 15, respectively.

Example 2:

Input: `root = [1]`  
Output: 0

## Solution

We are given the definition of a **binary tree node**:

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

We are also told that the number of nodes in the tree is in the range $[1, 1000]$ and that $-1000 \le \text{Node.val} \le 1000$.

We can implement a *recursive* approach by using a helper `int recLeftLeafSum(TreeNode* x)`, which *recursively* calculates the sum of all *left leaf nodes* of the subtree rooted at node $x$:  

 - if `x` is `nullptr` we return `0` as the base case.
 - otherwise, we initialize a variable `sum` to 0 in order to keep track of the sum found. We then check if node `x` has a left child and, if it does, we create a pointer to it `TreeNode* y = x->left`. We then check if `y` is a *leaf node*. 
    - if `y` is a *leaf node*, we update `sum` by adding its value `y->val`.
    - otherwise, we update `sum` by adding the result found when recursively checking the subtree rooted at node `y`.
 - we must still update the `sum` by also adding the result found when recursively checking the subtree rooted at `x.right`.

We can then have the function `sumOfLeftLeaves` act as a *wrapper function* to the recursive helper above, returning the result found when called on `root`.

```cpp
// recursive helper
int recLeftLeafSum(TreeNode* x) {

    // base case
    if (x == nullptr) {
        return 0;
    }

    // initialize sum
    int sum = 0;

    // if x has a left child
    if (x->left != nullptr) {

        //create pointer to it 
        TreeNode* y = x->left;

        // if y is a leaf node, we update the sum with its value
        if (y->left == nullptr && y->right == nullptr) {
            sum = sum + y->val;
        }

        // otherwise, we update the sum by recursively checking node y
        else {
            sum = sum + recLeftLeafSum(y);
        }
    }

    // we must still update the sum by recursively checking the right subtree
    sum = sum + recLeftLeafSum(x->right);
    return sum;
}

int sumOfLeftLeaves(TreeNode* root) {

    // call recursive procedure
    return recLeftLeafSum(root);
}
```

#### Complexity
Assuming the tree has $n$ nodes, the total **time complexity** in the worst case is $\mathcal{O}(n)$.

Assuming the tree has a height $h$, the total **space complexity** is $\mathcal{O}(h)$. In the worst case, this means $\mathcal{O}(n)$, and in the best case, this means $\mathcal{O}(\log n)$.
