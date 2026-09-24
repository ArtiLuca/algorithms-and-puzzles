#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        // create "dummy" node
        ListNode dummy;
        ListNode* current = &dummy;

        // initilize leftover carry is 0
        int carry = 0;

        // loop as long as l1 has nodes, l2 has nodes, or there is leftover carry
        while (l1 != nullptr|| l2 != nullptr || carry != 0) {

            // extract node values from both lists, if one list is empty, default to value 0
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;

            // compute sum of values plus any leftover carry, 
            // and update carry with integer division
            int sum = val1 + val2 + carry;
            carry = sum / 10;

            // allocate new node and store correct digit using modulo operator
            current->next = new ListNode(sum % 10);
            current = current->next;

            // if lists still have nodes, move to next 
            if (l1 != nullptr) {
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                l2 = l2->next;
            }
        }

        // return head of linked list with result, next node of "dummy"
        return dummy.next;
    }
};

void printLinkedList( ListNode* root) {

    if (!root) return;

    ListNode* x = root;

    std::cout << "[ ";
    while (x != nullptr) {
        std::cout << x->val << " ";
        x = x->next;
        
    }
    std::cout << "]\n" << std::endl; 
}

// memory cleanup
void deleteLinkedList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {

    Solution s;

    // Example 1:  
    // Input: l1 = [2,4,3], l2 = [5,6,4]  
    // Output: [7,0,8]  
    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    std::cout << "Example 1\nExpected Output: [ 7 0 8 ]" << std::endl;
    ListNode* root1 = s.addTwoNumbers(l1, l2);
    std::cout << "Output:          ";
    printLinkedList(root1);


    // Example 2:  
    // Input: l3 = [0], l4 = [0]  
    // Output: [0] 
    ListNode* l3 = new ListNode(0);
    ListNode* l4 = new ListNode(0);
    std::cout << "Example 2\nExpected Output: [ 0 ]" << std::endl;
    ListNode* root2 = s.addTwoNumbers(l3, l4);
    std::cout << "Output:          ";
    printLinkedList(root2);
    
    //Example 3:  
    //Input: l5 = [9,9,9,9,9,9,9], l6 = [9,9,9,9]
    //Output: [8,9,9,9,0,0,0,1]
    ListNode* l5 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9)))))));
    ListNode* l6 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))));
    std::cout << "Example 3\nExpected Output: [ 8 9 9 9 0 0 0 1 ]" << std::endl;
    ListNode* root3 = s.addTwoNumbers(l5, l6);
    std::cout << "Output:          ";
    printLinkedList(root3);


    // memory cleanup
    deleteLinkedList(l1);
    deleteLinkedList(l2);
    deleteLinkedList(root1);
    
    deleteLinkedList(l3);
    deleteLinkedList(l4);
    deleteLinkedList(root2);
    
    deleteLinkedList(l5);
    deleteLinkedList(l6);
    deleteLinkedList(root3);
    

    return 0;
}