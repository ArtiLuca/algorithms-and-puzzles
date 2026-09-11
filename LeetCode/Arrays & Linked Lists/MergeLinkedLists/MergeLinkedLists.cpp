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

    // recursive version
    ListNode* mergeTwoListsA(ListNode* list1, ListNode* list2) {

        // if both lists are empty, return NULL
        if (!list1 && !list2) 
            return nullptr;

        // if one list ends, we return the remaining one
        if (!list1) 
            return list2;
        if (!list2)
            return list1;
            
        // otherwise, return and set next pointer smaller
        if (list1->val < list2->val) {
            list1->next = mergeTwoListsA(list1->next, list2);
            return list1;
        }    
        else {
            list2->next = mergeTwoListsA(list1, list2->next);
            return list2;
        }
    }

    // iterative version
    ListNode* mergeTwoListsB(ListNode* list1, ListNode* list2) {

        // create temporary node ("dummy")
        ListNode* temp = new ListNode(-1);
        ListNode* current = temp;

        // iterate through both lists
        while (list1 != nullptr && list2 != nullptr) {

            // add smaller node to merged list
            if (list1->val <= list2->val) {
                current->next = list1;
                list1 = list1->next;
            }
            else {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }

        // if any list is left, add to end of merged list
        if (list1 != nullptr)
            current->next = list1;
        else
            current->next = list2;
        
        // return merged list, starting from the next node after temp
        ListNode* result = temp->next;
        delete temp;
        return result;
    }

    // helper for printing merged list
    void printList(ListNode* list) {

        if (list == nullptr) {
            std::cout << "[]" << std::endl;
            return;
        }
        while (list != nullptr) {
            std::cout << list->val;
            if (list->next != nullptr) {
                std::cout << " -> ";
            }
            list = list->next;
        }
        std::cout << std::endl; 
    }
};

int main() {

    Solution s;

    // Example 1: Output: [1,1,2,3,4,4]
    ListNode* list1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode* list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    std::cout << "Example 1 Merged (Iterative): ";
    ListNode* merged1_it = s.mergeTwoListsB(list1, list2);
    s.printList(merged1_it); 

    ListNode* list1_rec = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode* list2_rec = new ListNode(1, new ListNode(3, new ListNode(4)));
    std::cout << "Example 1 Merged (Recursive): ";
    ListNode* merged1_rec = s.mergeTwoListsA(list1_rec, list2_rec);
    s.printList(merged1_rec); 

    // Example 2: Empty lists
    ListNode* list3 = nullptr;
    ListNode* list4 = nullptr;
    std::cout << "Example 2 Merged: ";
    s.printList(s.mergeTwoListsB(list3, list4));

    // Example 3: Single element list
    ListNode* list5 = nullptr;
    ListNode* list6 = new ListNode(0);
    std::cout << "Example 3 Merged: ";
    s.printList(s.mergeTwoListsB(list5, list6));

    return 0;
}

