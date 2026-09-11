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

    bool isSameTree(TreeNode* p, TreeNode* q) {

        // if both are nullptr, they are the same
        if (p == nullptr && q == nullptr) {
            return true;
        }

        // if one is nullptr but other isn't, they are not the same
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
};

// helper for memory cleanup
void deleteTree(TreeNode* root) {

    if (!root) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    Solution s;

    // Example 1
    TreeNode* p1 = new TreeNode(1); p1->left = new TreeNode(2); p1->right = new TreeNode(3);
    TreeNode* q1 = new TreeNode(1); q1->left = new TreeNode(2); q1->right = new TreeNode(3);
    std::cout << "Example 1: " << s.isSameTree(p1, q1) << " (Expected: true)\n";

    // Example 2
    TreeNode* p2 = new TreeNode(1); p2->left = new TreeNode(2);
    TreeNode* q2 = new TreeNode(1); q2->right = new TreeNode(2); 
    std::cout << "Example 2: " << s.isSameTree(p2, q2) << " (Expected: false)\n";

    // Example 3
    TreeNode* p3 = new TreeNode(1); p3->left = new TreeNode(2); p3->right = new TreeNode(1);
    TreeNode* q3 = new TreeNode(1); q3->left = new TreeNode(1); q3->right = new TreeNode(2);
    std::cout << "Example 3: " << s.isSameTree(p3, q3) << " (Expected: false)\n";

    // Example 4
    TreeNode* p4 = new TreeNode(1); 
    p4->left = new TreeNode(2); p4->right = new TreeNode(3); p4->left->left = new TreeNode(4); p4->left->right = new TreeNode(5); 
    p4->right->left = new TreeNode(6); p4->right->right = new TreeNode(7); p4->left->left->left = new TreeNode(8);

    TreeNode* q4 = new TreeNode(1);
    q4->left = new TreeNode(2); q4->right = new TreeNode(3); q4->left->left = new TreeNode(4); q4->left->right = new TreeNode(5);
    q4->right->left = new TreeNode(6); q4->right->right = new TreeNode(7); q4->left->left->left = new TreeNode(8);
    std::cout << "Example 4: " << s.isSameTree(p4, q4) << " (Expected: true)\n";

    // memory cleanup
    deleteTree(p1); deleteTree(q1);
    deleteTree(p2); deleteTree(q2);
    deleteTree(p3); deleteTree(q3);
    deleteTree(p4); deleteTree(q4);

    return 0;
 }
