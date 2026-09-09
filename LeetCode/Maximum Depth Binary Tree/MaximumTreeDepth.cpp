#include <iostream>
#include <algorithm>

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

    int maxDepth(TreeNode* root) {

        // base case
        if (root == nullptr) {
            return 0;
        }

        int leftHeight = maxDepth(root->left);
        int rightHeight = maxDepth(root->right);

        // update maximum depth
        return std::max(leftHeight, rightHeight) + 1;
    }
};

int main() {

    Solution s;

    // Example 1
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    std::cout << "Max Depth = " << s.maxDepth(root1) << std::endl;

    // Example 2
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    std::cout << "Max Depth = " << s.maxDepth(root2) << std::endl;

    // Clean up allocated memory...

    return 0;
}
