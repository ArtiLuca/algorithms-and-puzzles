#include <iostream>

struct TreeNode {

    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    int sumOfLeftLeaves(TreeNode* root) {

        // call recursive procedure
        return recLeftLeafSum(root);
    }

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
            // ceate pointer to it 
            TreeNode* y = x->left;
            // if y is a leaf node, we update the sum with its value
            if (y->left == nullptr && y->right == nullptr) {
                sum = sum + y->val;
            }
            // otherwise, we update the sum by recursively check node y
            else {
                sum = sum + recLeftLeafSum(y);
            }
        }
        // we must still update the sum by recursively checking the right subtree
        sum = sum + recLeftLeafSum(x->right);
        return sum;
    }
};

// cleanup
void deleteTree(TreeNode* root) {

    if (root == nullptr) {
        return;
    }
    
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    Solution s;

    // Example 1 (24)
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    std::cout << "Example 1 Output: " << s.sumOfLeftLeaves(root1) << " (Expected: 24)\n";

    // Example 2 (0)
    TreeNode* root2 = new TreeNode(1);
    std::cout << "Example 2 Output: " << s.sumOfLeftLeaves(root2) << " (Expected: 0)\n";

    // Example 3 (16)
    TreeNode* root3 = new TreeNode(5);
    // Left side of root
    root3->left = new TreeNode(2);
    root3->left->left = new TreeNode(1);
    root3->left->left->left = new TreeNode(3); // Left Leaf #1
    root3->left->right = new TreeNode(4);
    root3->left->right->left = new TreeNode(6); // Left Leaf #2

    // Right side of root
    root3->right = new TreeNode(8);
    root3->right->left = new TreeNode(7); // Left Leaf #3
    root3->right->right = new TreeNode(9);
    root3->right->right->right = new TreeNode(10);
    std::cout << "Example 3 Output: " << s.sumOfLeftLeaves(root3) << " (Expected: 16)\n";

    // cleanup
    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root3);

    return 0;
}
