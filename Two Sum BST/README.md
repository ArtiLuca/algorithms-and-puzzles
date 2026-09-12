# Two Sum - Input is BST

Problem: [LeetCode](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/)

Given the `root` of a binary search tree and an integer `k`, return `true` *if there exist two elements in the BST such that their sum is equal to* `k`, or `false` *otherwise*.

Example 1:

![sumtree1](sum_tree_1.jpg)

Input: $root = [5,3,6,2,4,null,7]$, $k = 9$  
Output: true

Example 2:

![sumtree2](sum_tree_2.jpg)

Input: $root = [5,3,6,2,4,null,7]$, $k = 28$  
Output: false

## Solution

We are told the number of nodes in the tree is in the range $\in [1, 10^{4}]$, that $-10^{4} \le \text{Node.val} \le 10^{4}$, that `root` is guaranteed to be a valid **binary search tree**, and that $-10^{5} \le k \le 10^{5}$.

We are also given the definition of a **binary tree node**:

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

Two different ideas came to my mind for implementing a solution to this problem.

### First approach: Depth-First-Search using Hash Set

To implement the two-sum solution using a **BST** as input we can use a *recursive* approach that makes use of a **hash set** `std::unordered_set seen` that tracks the nodes we have already seen as we traverse the **BST**. We can use this **hash set** alongside a boolean helper `bool targetFound(TreeNode* node, int k)` to check whether the target sum was reached when evaluating the current node:  

 - if the current `node` is `nullptr`, the target sum cannot be reached, so we return `false`.
 - if the complement of the current `node` exists in our hash set, meaning `seen.count(k - node->val)` returns 1, then we have reached the target sum and we return `true`.
 - otherwise, we **insert** the current `node` in the **hash set** and then continue the search by *recursively* checking if the result was found by moving to the **left subtree** of the current `node` or the **right subtree** of the current `node`. 
 
We can then use this boolean helper inside the main function `bool findTarget(TreeNode* root, int k)`, which now simply acts as a *wrapper* function.

#### Pseudocode

Assuming `std::unordered_set<int> seen` is a private member of the class `Solution`:

```cpp
// recursive helper 
bool targetFound(TreeNode* node, int k) {

    // if current node is nullptr, target cannot be reached
    if (node == nullptr) {
        return false;
    }

    // if complement of current node exists in set, target was found
    if (seen.count(k - node->val)) {
        return true;
    }

    // otherwise, we insert current node's value in set 
    seen.insert(node->val);

    // and recursively check if result is found in either left or right subtree
    return targetFound(node->left, k) || targetFound(node->right, k);
}

bool findTarget(TreeNode* root, int k) {
    
    // cleanup previous
    seen.clear();
    return targetFound(root, k);
}
```
 
#### Complexity
Assuming there are $n$ nodes in total, the total **time complexity** in the worst case is $\mathcal{O}(n)$, with the hash set operating with a constant cost of $\mathcal{O}(1)$ on average.

The total **space complexity** is given by the hash set and recursion call stack. In the worst case, the **hash set** stores all $n$ elements and the recursion stack uses $\mathcal{O}(h)$ space, where $h$ is the height of the tree. Together, these lead to a total space complexity of $\mathcal{O}(n)$.

### Second approach: BST iterator stack
We can mimic the standard **two-pointer** technique used on sorted arrays by using two `std::stack` objects to traverse the **BST** from the left (*smallest to largest*) and right (*largest to smallest*) simultaneously.

The main idea is to *simulate* an **in-order** and **reverse in-order** traversal without storing the node values in an array.

We use two `std::stack` objects to track the active paths to the current *smallest* and *largest* elements of the tree:

 - `nextStack` is the *left pointer* and is initialized by pushing the **root** and all of its **left subtree** to quickly find the absolute minimum value.
 - `prevStack` is the *right pointer* and is initialized by pushing the **root** and all of its **right subtree** to quickly find the absolute maximum value. 

During the traversal, we inspect the values at the **top** of both stacks and check their sum. If their sum is **smaller** than $k$, we advance the *left pointer* by **popping** from `nextStack` and pushing its right child's leftmost path. If the sum is **larger** than $k$, we move the *right pointer* backwards by **popping** from `prevStack` and pushing its left child's rightmost path.

This process continues until a match is found or the two pointers meet at the exact same node.

#### Pseudocode

```cpp
bool findTarget(TreeNode* root, int k) {

    if (root == nullptr) {
        return false;
    }

    // simulate two-pointers using stacks
    std::stack<TreeNode*> nextStack; // ascending order (left to right)
    std::stack<TreeNode*> prevStack; // descending order (right to left)

    // initialize left pointer (smallest element)
    TreeNode* current = root;
    while (current) {
        nextStack.push(current);
        current = current->left;
    }

    // initialize right pointer (largest element)
    current = root;
    while (current) {
        prevStack.push(current);
        current = current->right;
    }

    // two-pointer traversal 
    while (!nextStack.empty() && !prevStack.empty()) {

        TreeNode* leftNode = nextStack.top();
        TreeNode* rightNode = prevStack.top();

        // if pointers meet at the same node
        if (leftNode == rightNode) {
            break;
        }

        // if target sum was reached
        int currentSum = leftNode->val + rightNode->val;
        if (currentSum == k) {
            return true;
        }

        // if sum is too small, move the left pointer forward
        if (currentSum < k) {
            nextStack.pop();
            TreeNode* node = leftNode->right;
            while (node) {
                nextStack.push(node);
                node = node->left;
            }
        }

        // if sum is too large, move the right pointer backwards
        else {
            prevStack.pop();
            TreeNode* node = rightNode->left;
            while (node) {
                prevStack.push(node);
                node = node->right;
            }
        }
    }

    // if target sum never reached
    return false;
}
```

#### Complexity
The total **time complexity** is $\mathcal{O}(n)$ in the worst case, however due to *early terminations* this is usually not the case.

Assuming $h$ is the height of the tree, the two **stacks** only store the nodes from a single $\text{root} \to \text{leaf}$ path at any given time, meaning the combined elements in both of them will be at the most $2 \times h$. If the **binary search tree** is balanced, this means that the total **space complexity** evaluates to $\mathcal{O}(\log n)$.

