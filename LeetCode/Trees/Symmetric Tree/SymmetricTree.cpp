#include <iostream>
#include <string>
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

    // iterative indicates whether to invoke recursive or iterative implementation
    bool isSymmetric(TreeNode* root, bool iterative = false) {
        
        if (!iterative) {
            return isSymmetricRecursive(root);
        }
        else {
            return isSymmetricIterative(root);
        }
    }

    // recursive approach
    bool isSymmetricRecursive(TreeNode* root) {

        // if the tree is empty, it is symmetric by default
        if (!root) {
            return true;
        }

        // otherwise, use helper to check left and right subtrees
        return isSymmetricRec(root->left, root->right);
    }

    // helper for implementing recursive logic
    bool isSymmetricRec(TreeNode* t1, TreeNode* t2) {

        // if both are nullptr, they are symmetric by default
        if (!t1 && !t2) {
            return true;
        }

        // if only one is nullptr (XOR), they are not symmetric
        if (!t1 || !t2) {
            return false;
        }

        // if the values do not match, they are not symmetric
        if (t1->val != t2->val) {
            return false;
        }

        // recursively check that outer and inner paths are symmetric
        return isSymmetricRec(t1->left, t2->right) && isSymmetricRec(t1->right, t2->left);
    }

    bool isSymmetricIterative(TreeNode* root) {

        // if the tree is empty, it is symmetric by default
        if (!root) {
            return true;
        }

        // allocate queue structure for tree nodes
        std::queue<TreeNode*> q;

        // initially, push left and right subtrees
        q.push(root->left);
        q.push(root->right);

        // loop as long as queue has nodes
        while (!q.empty()) {

            // extract pair of nodes from front of the queue
            TreeNode* t1 = q.front();
            q.pop();
            TreeNode* t2 = q.front();
            q.pop();

            // if both are nullptr, they are symmetric by default, continue
            if (!t1 && !t2) {
                continue;
            }
            
            // if only one is nullptr (XOR), they are not symmetric, return false
            if (!t1 || !t2) {
                return false;
            }
            
            // if the values do not match, they are not symmetric, return false
            if (t1->val != t2->val) {
                return false;
            }

            // push "outer path" into queue
            q.push(t1->left);
            q.push(t2->right);
            // push "inner path" into queue
            q.push(t1->right);
            q.push(t2->left);
        }

        // if all pairs were found to be symmetric, then I return true
        return true;
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

void printTest(const std::string& lbl, const std::string& nodes, TreeNode* root, bool iterative) {
    Solution s;
    bool result = s.isSymmetric(root, iterative);
    
    std::string approach = iterative ? "[Iterative]" : "[Recursive]";
    
    std::cout << "--------------------------------------------------------\n";
    std::cout << approach << " " << lbl << "\n";
    std::cout << "Tree Nodes:  [ " << nodes << " ]\n";
    std::cout << "Result:      " << (result ? "✅ Tree is symmetric" : "❌ Tree is NOT symmetric") << "\n";
}

int main() {

    // Example 1: (Symmetric)
    TreeNode* t1 = new TreeNode(1,
        new TreeNode(2, new TreeNode(3), new TreeNode(4)),
        new TreeNode(2, new TreeNode(4), new TreeNode(3))
    );
    printTest("Example 1 (Expected: Symmetric)", "1, 2, 2, 3, 4, 4, 3", t1, false);
    
    
    // Example 2: (Asymmetric)
    TreeNode* t2 = new TreeNode(1,
        new TreeNode(2, nullptr, new TreeNode(3)),
        new TreeNode(2, nullptr, new TreeNode(3))
    );
    printTest("Example 2 (Expected: NOT Symmetric)", "1, 2, 2, null, 3, null, 3", t2, true);

    
    // Example 3: (Symmetric)
    TreeNode* t3 = new TreeNode(1,
        new TreeNode(2, new TreeNode(3), nullptr),
        new TreeNode(2, nullptr, new TreeNode(3))
    );
    printTest("Example 3 (Expected: Symmetric)", "1, 2, 2, 3, null, null, 3", t3, true);


    // Example 4: (Asymmetric)
    TreeNode* t4 = new TreeNode(1,
        new TreeNode(2, new TreeNode(3), nullptr),
        new TreeNode(2, new TreeNode(3), nullptr)
    );
    printTest("Example 4 (Expected: NOT Symmetric)", "1, 2, 2, 3, null, 3, null", t4, false);


    // Example 5: (Symmetric)
    TreeNode* t5 = new TreeNode(1);
    printTest("Example 5 (Expected: Symmetric)", "1", t5, true);


    // Example 6: (Symmetric)
    TreeNode* t6 = new TreeNode(1,
        // Left Subtree
        new TreeNode(2,
            new TreeNode(3, new TreeNode(5), new TreeNode(6)),
            new TreeNode(4, new TreeNode(7), new TreeNode(8))
        ),
        // Right Subtree 
        new TreeNode(2,
            new TreeNode(4, new TreeNode(8), new TreeNode(7)),
            new TreeNode(3, new TreeNode(6), new TreeNode(5))
        )
    );
    printTest("Example 6 (Expected: Symmetric)", "1, 2, 2, 3, 4, 4, 3, 5, 6, 7, 8, 8, 7, 6, 5", t6, false);


    // Example 7: (Asymmetric)
    TreeNode* t7 = new TreeNode(1,
        // Left Subtree
        new TreeNode(2,
            new TreeNode(3, new TreeNode(5), new TreeNode(6)),
            new TreeNode(4, nullptr, new TreeNode(7)) 
        ),
        // Right Subtree
        new TreeNode(2,
            new TreeNode(4, new TreeNode(8), new TreeNode(7)), 
            new TreeNode(3, new TreeNode(6), new TreeNode(5))
        )
    );
    printTest("Example 7 (Expected: NOT Symmetric)", "1, 2, 2, 3, 4, 4, 3, 5, 6, null, 7, 8, 7, 6, 5", t7, true);

   
    // memory cleanup...
    deleteTree(t1);
    deleteTree(t2);
    deleteTree(t3);
    deleteTree(t4);
    deleteTree(t5);
    deleteTree(t6);
    deleteTree(t7);

    return 0;
}
