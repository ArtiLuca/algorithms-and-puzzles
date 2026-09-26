#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    ListNode* deleteDuplicates(ListNode* head) {

        // if the list is empty, nothing to do
        if (!head) {
            return nullptr;
        }

        // create pointer to head of list
        ListNode* current = head;

        // iterate through list as long as there are nodes to check
        while (current && current->next) {

            // if I find two consecutive nodes with the same value, I found a duplicate
            if (current->val == current->next->val) {

                // create temporary pointer to the duplicate node
                ListNode* duplicate = current->next;
                
                // update current node so that it skips the duplicate 
                current->next = current->next->next;
                
                // remove the duplicate from the list
                delete duplicate;
            }  
            else { // otherwise, advance current node  
                current = current->next;
            }
        }
        // return head of list after removing all duplicates
        return head;
    }
};

void printList(ListNode* head) {
    
    ListNode* x = head;

    std::cout << "[ ";
    while (x != nullptr) {
        std::cout << x->val << " ";
        x = x->next;
    }
    std::cout << "]" << std::endl;
}

void deleteList(ListNode* head) {

    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {

    Solution s;

    // Example 1: 1,1,2    
    ListNode* l1 = new ListNode(1, new ListNode(1, new ListNode(2)));
    std::cout << "Example 1:" << std::endl;
    std::cout << "Input:  ";
    printList(l1);
    std::cout << "Output: ";
    printList(s.deleteDuplicates(l1));
    std::cout << std::endl;

    // Example 2: 1,1,2,3,3
    ListNode* l2 = new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3)))));
    std::cout << "Example 2:" << std::endl;
    std::cout << "Input:  ";
    printList(l2);
    std::cout << "Output: ";
    printList(s.deleteDuplicates(l2));
    std::cout << std::endl;

    // Example 3: 2,3,4,4,4,5,6,6
    ListNode* l3 = new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(4, new ListNode(4, new ListNode(5, new ListNode(6, new ListNode(6))))))));
    std::cout << "Example 3:" << std::endl;
    std::cout << "Input:  ";
    printList(l3);
    std::cout << "Output: ";
    printList(s.deleteDuplicates(l3));
    std::cout << std::endl;

    

    // Example 4: 1,2,3,4,5
    ListNode* l4 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    std::cout << "Example 4:" << std::endl;
    std::cout << "Input:  ";
    printList(l4);
    std::cout << "Output: ";
    printList(s.deleteDuplicates(l4));
    std::cout << std::endl;

    // Example 5: 1,2,3,3,3,3
    ListNode* l5 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3, new ListNode(3, new ListNode(3))))));
    std::cout << "Example 5:" << std::endl;
    std::cout << "Input:  ";
    printList(l5);
    std::cout << "Output: ";
    printList(s.deleteDuplicates(l5));
    std::cout << std::endl;

    // memory cleanup
    deleteList(l1);
    deleteList(l2);
    deleteList(l3);
    deleteList(l4);
    deleteList(l5);

    return 0;
}