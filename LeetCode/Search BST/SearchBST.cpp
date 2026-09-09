#include <iostream>
#include <queue>

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
};

// helper for printing result
void printResult(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "[]\n";
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);
    std::cout << "[";

    bool first = true;
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr != nullptr) {
            if (!first) std::cout << ", ";
            std::cout << curr->val;
            first = false;

            q.push(curr->left);
            q.push(curr->right);
        }
    }
    std::cout << "]\n";
}


int main() {

    Solution s;

    TreeNode* root = new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7));

    // Example 1
    std::cout << "Val=2\n";
    TreeNode* t1 = s.searchBST(root, 2);
    printResult(t1);


    // Example 2
    std::cout << "Val=5\n";
    TreeNode* t2 = s.searchBST(root, 5);
    printResult(t2);


    return 0;
}
