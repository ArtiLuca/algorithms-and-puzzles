# Add Two Numbers

Problem: [LeetCode](https://leetcode.com/problems/add-two-numbers/description/)

You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse** order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

![addtwonumber](addtwonumber1.jpg)

Example 1:  
Input: $l1 = [2,4,3]$, $l2 = [5,6,4]$  
Output: $[7,0,8]$  
Explanation: $342 + 465 = 807$.

Example 2:  
Input: $l1 = [0]$, $l2 = [0]$  
Output: $[0]$ 

Example 3:  
Input: $l1 = [9,9,9,9,9,9,9]$, $l2 = [9,9,9,9]$  
Output: $[8,9,9,9,0,0,0,1]$

## Solution

We are told that the number of nodes in each linked list is in the range $\in [1, 100]$, that $0 \le \text{Node.val} \le 9$, and that tt is guaranteed that the list represents a number that does not have leading zeros.

We are also given the definition of a **singly-linked list**:

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

Since we are not given any information on the number of elements, we can't transform the list into it's corresponding numerical value as it could cause *integer overflow*. However, we are helped by the fact that both linked lists `l1` and `l2` are in **reverse order**.  

We can implement a solution by using standard addition and building a new **linked list** by summing the two nodes of `l1` and `l2`.  
Since the digits can only be $[0 \dots 9]$ we also use a variable `carry` to take into account any *leftover carry values* from the previous operation. So, when evaluating the sum between two nodes we evaluate the sum of the two node values plus any leftover carryover. For any given sum between two nodes the *leftover carry* can be found using *integer division*: 

$\text{carry } = \text{ sum } \div 10$.

The actual digit stored in the new linked list for any given sum can be found using the *modulo operator*: 

$\text{digit } = \text{ sum } \mod 10$.

Since one list may contain more elements, we can check for `nullptr` nodes and have them act as if having a value of $0$ as to not influence the result. We continue with this as long *as at least one* linked list still has elements, **OR** there is a *leftover carry*. If there is any *leftover carry* after both lists have been exhausted, we then must allocate a new node to deal with this.

As an example we can consider:
 - $l1 = 3 \rarr 5 \rarr 9 \rarr 2$
   - representing $3 \times 10^{0} + 5 \times 10^{1} + 9 \times 10^{2} + 2 \times 10^{3} = 3 + 50 + 900 + 2000 = 2953$
 - $l2 = 7 \rarr 1 \rarr 3 \rarr 5 \rarr 8$
   - representing $7 \times 10^{0} + 1 \times 10^{1} + 3 \times 10^{2} + 5 \times 10^{3} + 8 \times 10^4 = 7 + 10 + 300 + 5000 + 80000 = 85317$

If we sum the two corresponding numerical values we have $2953 + 85317 = 88270$. We want the **new linked list** containing the resulting sum to have the corresponding digits, in **reverse order**.  

The operation would be as follows, where `sum` and `carry` are used to indicate the sum of two node values and any *leftover carry*, and `digit` is used to indicate the digit stored in the new linked list with the result. Initially, `carry = 0`:

 - `sum` = $3+7+0=10$; `carry` = $10 \div 10 = 1$; `digit` = $10 \mod 10 = 0$;
   - we insert $0$ 
 - `sum` = $5+1+1 = 7$; `carry` = $7 \div 10 = 0$; `digit` = $7 \mod 10 = 7$
   - we insert $7$
 - `sum` = $9+3+0=12$; `carry` = $12 \div 10 = 1$; `digit` = $12 \mod 10 = 2$
   - we insert $2$
 - `sum` = $2+5+1=8$; `carry` = $8 \div 10 = 0$; `digit` = $8 \mod 10 = 8$     
   - we insert $8$
 - at this point the first list contains no more nodes, so `sum` = $0+8+0=8$; `carry` = $8 \div 10 = 0$; `digit` = $8 \mod 10 = 8$  
   - we insert $8$ as the final node, since `carry = 0` and therefore no extra node must be allocated.

The final constructed linked list containing the result would be, in this case:

$L_{\text{result}} = 0 \rarr 7 \rarr 2 \rarr 8 \rarr 8$.

#### Pseudocode

```cpp 
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    // create "dummy" node
    ListNode dummy;
    ListNode* current = &dummy;

    // initilize leftover carry is 0
    int carry = 0;

    // loop as long as l1 has nodes, l2 has nodes, or there is leftover carry
    while (l1 != nullptr || l2 != nullptr || carry != 0) {

        // extract node values from both lists, if one list is empty, default to value 0
        int val1 = (l1 != nullptr) ? l1->val : 0; 
        int val2 = (l2 != nullptr) ? l2->val : 0; 

        // compute sum of values plus any leftover carry, and update carry with integer division
        int sum = val1 + val2 + carry;
        carry = sum / 10;

        // allocate new node and store value using modulo operator
        current->next = new ListNode(sum % 10);
        current = current->next;

        // if lists still have nodes, move to next 
        if (l1 != nullptr) { l1 = l1->next; }
        if (l2 != nullptr) { l2 = l2->next; }
    }

    // return head of new linked list
    return dummy.next;
}
```

#### Complexity
Assuming `l1` contains $n_{1}$ nodes and `l2` contains $n_{2}$ nodes, the loops runs at the most $\max(n_{1}, n_{2}) + 1$ times, where the extra $+1$ represents the potential *leftover carry*. If $n = \max(n_{1}, n_{2})$, the total **time complexity** in the worst case is $\mathcal{O}(n)$.

Since we allocate a **new** linked list, this means that the total **space complexity** is also $\mathcal{O}(n)$.