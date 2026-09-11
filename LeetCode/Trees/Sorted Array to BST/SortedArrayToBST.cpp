#include <iostream>
#include <vector>
#include <queue>
#include <string>

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
    
    TreeNode* sortedArrayToBST(std::vector<int>& nums) {

        return arrayToBSTrec(nums, 0, nums.size() - 1);
    }

private:  

    // recursive helper procedure
    TreeNode* arrayToBSTrec(std::vector<int>& nums, int p, int r) {

        // base case
        if (p > r) {
            return nullptr;
        }

        // compute midpoint index
        int q = p + (r - p) / 2;
        TreeNode* x = new TreeNode(nums[q]);

        // recursively build left subtree
        x->left = arrayToBSTrec(nums, p, q-1);

        // recursively build right subtree
        x->right = arrayToBSTrec(nums, q+1, r);

        // return root
        return x;
    }

};

void printResult(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "[]\n";
        return;
    }

    std::vector<std::string> res;
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr != nullptr) {
            res.push_back(std::to_string(curr->val));
            q.push(curr->left);
            q.push(curr->right);
        } else {
            res.push_back("null");
        }
    }

    // Trim trailing "null" elements to match clean LeetCode style
    while (!res.empty() && res.back() == "null") {
        res.pop_back();
    }

    // Print out the vector formatted
    std::cout << "[";
    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i];
        if (i < res.size() - 1) std::cout << ",";
    }
    std::cout << "]\n";
}

void deleteTree(TreeNode* root) {

    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    Solution s;

    // Example 1
    std::vector<int> nums1 = {-10,-3,0,5,9};
    std::cout << "Example 1:\n";
    TreeNode* x1 = s.sortedArrayToBST(nums1);
    printResult(x1);

    // Example 2
    std::vector<int> nums2 = {1,3};
    std::cout << "Example 2:\n";
    TreeNode* x2 = s.sortedArrayToBST(nums2);
    printResult(x2);

    // Example 3
    std::vector<int> nums3 = {2,8,12,14,16,20,21,22,24,25,30};
    std::cout << "Example 3:\n";
    TreeNode* x3 = s.sortedArrayToBST(nums3);
    printResult(x3);

    // memory cleanup
    deleteTree(x1);
    deleteTree(x2);
    deleteTree(x3);

    return 0;
}