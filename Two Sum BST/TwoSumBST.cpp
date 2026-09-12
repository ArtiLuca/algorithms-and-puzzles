#include <iostream>
#include <unordered_set>
#include <stack>

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

    // using DFS hash-set approach
    bool findTargetA(TreeNode* root, int k) {
        seen.clear();
        return targetFound(root, k);
    }

    // using BST iterator approach
    bool findTargetB(TreeNode* root, int k) {

        if (root == nullptr) {
            return false;
        }

        // simulate two-pointers using stacks
        std::stack<TreeNode*> nextStack;
        std::stack<TreeNode*> prevStack;

        // initialize left pointer (smallest element)
        TreeNode* curr = root;
        while (curr) {
            nextStack.push(curr);
            curr = curr->left;
        }

        // initialize right pointer (largest element)
        curr = root;
        while(curr) {
            prevStack.push(curr);
            curr = curr->right;
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
            int sum = leftNode->val + rightNode->val;
            if (sum == k) {
                return true;
            }

            // if sum is too small, move the left pointer forward
            if (sum < k) {
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

        // if target sum was never reached
        return false;
    }

private:

    // hash set
    std::unordered_set<int> seen;

    // helper for DFS hash-set approach

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
};

// memory cleanup
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    
    Solution s;

    // Example 1:
    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(3, new TreeNode(2), new TreeNode(4));
    root1->right = new TreeNode(6, nullptr, new TreeNode(7));
    
    std::cout << "--- Example 1 ---" << std::endl;
    std::cout << "DFS Hash-Set (k = 9):   " << (s.findTargetA(root1, 9) ? "Found" : "Not Found") << " (Expected: Found)" << std::endl;
    std::cout << "BST Iterator (k = 9):   " << (s.findTargetB(root1, 9) ? "Found" : "Not Found") << " (Expected: Found)" << std::endl;
    std::cout << "DFS Hash-Set (k = 28):  " << (s.findTargetA(root1, 28) ? "Found" : "Not Found") << " (Expected: Not Found)" << std::endl;
    std::cout << "BST Iterator (k = 28):  " << (s.findTargetB(root1, 28) ? "Found" : "Not Found") << " (Expected: Not Found)" << std::endl << std::endl;

    // Example 2:
    TreeNode* root2 = new TreeNode(6);
    root2->left = new TreeNode(3, new TreeNode(1, nullptr, new TreeNode(2)), new TreeNode(4, nullptr, new TreeNode(5)));
    root2->right = new TreeNode(9, new TreeNode(7, nullptr, new TreeNode(8)), new TreeNode(10, nullptr, new TreeNode(11)));

    std::cout << "--- Example 2 (11 Nodes) ---" << std::endl;
    std::cout << "DFS Hash-Set (k = 13):  " << (s.findTargetA(root2, 13) ? "Found" : "Not Found") << " (Expected: Found)" << std::endl;
    std::cout << "BST Iterator (k = 13):  " << (s.findTargetB(root2, 13) ? "Found" : "Not Found") << " (Expected: Found)" << std::endl;
    std::cout << "DFS Hash-Set (k = 40):  " << (s.findTargetA(root2, 40) ? "Found" : "Not Found") << " (Expected: Not Found)" << std::endl;
    std::cout << "BST Iterator (k = 40):  " << (s.findTargetB(root2, 40) ? "Found" : "Not Found") << " (Expected: Not Found)" << std::endl << std::endl;

    // Example 3:
    TreeNode* root3 = new TreeNode(40);
    root3->left = new TreeNode(20, new TreeNode(10), new TreeNode(30));
    root3->right = new TreeNode(60, new TreeNode(50), new TreeNode(70));

    std::cout << "--- Example 3 (7 Nodes) ---" << std::endl;
    std::cout << "DFS Hash-Set (k = 80):  " << (s.findTargetA(root3, 80) ? "Found" : "Not Found") << " (Expected: Found)" << std::endl;
    // Fixed: changed root1 to root3 below
    std::cout << "BST Iterator (k = 80):  " << (s.findTargetB(root3, 80) ? "Found" : "Not Found") << " (Expected: Found)" << std::endl; 
    std::cout << "DFS Hash-Set (k = 100): " << (s.findTargetA(root3, 100) ? "Found" : "Not Found") << " (Expected: Not Found)" << std::endl;
    std::cout << "BST Iterator (k = 100): " << (s.findTargetB(root3, 100) ? "Found" : "Not Found") << " (Expected: Not Found)" << std::endl << std::endl;

    // memory cleanup
    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root3);

    return 0;
}


