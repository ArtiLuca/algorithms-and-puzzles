#include <iostream>
#include <vector>
#include <stack>

// Definition for a binary tree node.
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

    // recursive version
    std::vector<int> inorderTraversalRec(TreeNode* root) {

        std::vector<int> result;
        helper(root, result);
        return result;
    }
    
    // iterative version
    std::vector<int> inorderTraversalIter(TreeNode* root) {

        std::vector<int> result;
        std::stack<TreeNode*> s;
        TreeNode* curr = root;

        while (curr != nullptr || !s.empty()) {

            // push left children of current node to stack
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }

            // move to leftmost unvisited node (top node)
            curr = s.top();
            s.pop();
            result.push_back(curr->val);

            // move to right subtree
            curr = curr->right;
        }

        return result;
    }

private:

    // helper for recursive logic
    void helper(TreeNode* root, std::vector<int>& result) {

        if (root == nullptr) {
            return;
        }

        helper(root->left, result);
        result.push_back(root->val);
        helper(root->right, result);
    }

};

// helper for printing result
void printResult(const std::vector<int>& result) {

    std::cout << "[";
    for (int i = 0; i < (int)result.size(); i++) {
        std::cout << result[i];
        if (i < (int)result.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

int main() {

    Solution s;

    // Example 1
    std::cout << "Example 1 (Recursive)\n";

    TreeNode* ex1 = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));
    printResult(s.inorderTraversalRec(ex1));

    std::cout << "\n";


    // Example 2
    std::cout << "Example 2 (Iterative)\n";
    
    // Bottom level nodes
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n9 = new TreeNode(9);

    // Middle level nodes
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5, n6, n7);
    TreeNode* n8 = new TreeNode(8, n9, nullptr);

    // Top level children
    TreeNode* n2 = new TreeNode(2, n4, n5);
    TreeNode* n3 = new TreeNode(3, nullptr, n8);

    // Root
    TreeNode* ex2 = new TreeNode(1, n2, n3);
    
    printResult(s.inorderTraversalIter(ex2));
    std::cout << "\n";


    // Example 3
    std::cout << "Example 3 (Iterative)\n";
    TreeNode* ex3 = nullptr;
    printResult(s.inorderTraversalIter(ex3));
    std::cout << "\n";


    // Example 4
    std::cout << "Example 4 (Recursive)\n";
    TreeNode* ex4 = new TreeNode(1);
    printResult(s.inorderTraversalRec(ex4));
    std::cout << "\n";

    // Since we allocate new nodes, we should delete them, using for example
    // deleteTree(TreeNode* root) 
    // not implemented  

    return 0;
}