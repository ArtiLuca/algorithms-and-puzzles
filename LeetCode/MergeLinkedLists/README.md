# Merge Two Sorted Linked List

Problem: [Merge Two Sorted Linked Lists](https://leetcode.com/problems/merge-two-sorted-lists/)

You are given the heads of two sorted linked lists `list1` and `list2`.

Merge the two lists into one **sorted** list. The list should be made by splicing together the nodes of the first two lists.

Return the *head of the merged linked list*.


![example image](merge_ex1.jpg)


## Solution

As a reminder, we are given the definition of a *singly-linked list*:

```cpp
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

### Idea
We are told that the number of nodes in both lists is in the range $[0, 50]$ and that

$$
-100 <= \text{ Node.val } <= 100
$$

Both `list1` and `list2` are sorted in **non-decreasing** order. We can use a *recursive* approach or an *iterative* approach.

In the *recursive* approach we start at the head of both lists `list1` and `list2`.
If either one is empty (`nullptr`), we can immediately return the other list as the remaining part to be merged.

Otherwise, we compare the current element of both lists and select the smaller one. 
We set the `next` pointer of the selected node to the node returned by the recursive call to `mergeTwoLists`, in which we pass the remaining elements of that list as well as the entire second list.

The recursive call `mergeTwoLists` *connects* elements from smallest to largest.
If one list ends before the other, then we simply append the rest of the remaining list (handled by the base case). 

#### Pseudocode

```cpp
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
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
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }    
    else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}
```

#### Complexity
For the recursive version, if $n$ is the size of the first list and $m$ is the size of the second list, then the total **time complexity** is $\mathcal{O}(n+m)$.

The total **space complexity** needed by the recursive calls on the stack is also $\mathcal{O}(n+m)$.

---

The *iterative* approach merges the two linked lists using a temporary *dummy* node. 

Using a `current` pointer to track the temporary *dummy* node and loop through both lists at the same time.
At each step, we compare the nodes from both lists, append the smaller node to `current->next`, and then move that specific list's head to the next node.

Once the loop ends (because one list has no elements remaining), we merge the rest of the remaining unfinished list directly to the end of the currently merged list.

#### Pseudocode

```cpp
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
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
        
    // store head of merged list, cleanup and return
    ListNode* result = temp->next;
    delete temp;
    return result;
} 
```

#### Complexity
In the iterative version, if $n$ is the size of the first list and $m$ is the size of the second list, then the total **time complexity** is $\mathcal{O}(n+m)$.

The total **space complexity** is in this case constant $\mathcal{O}(1)$.
