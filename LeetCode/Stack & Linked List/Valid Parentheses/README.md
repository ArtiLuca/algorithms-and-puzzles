# Valid Parentheses

Problem: [LeetCode](https://leetcode.com/problems/valid-parentheses/description/)

Given a string `s` containing just the characters `'(', ')', '{', '}', '['` and `']'`, determine if the input string is valid.

An input string is valid if:  

 - Open brackets must be closed by the same type of brackets.
 - Open brackets must be closed in the correct order
 - Every close bracket has a corresponding open bracket of the same type.


Example 1:  
Input: `s = "()"`  
Output: `true`

Example 2:  
Input: `s = "()[]{}"`  
Output: `true`

Example 3:  
Input: `s = "(]"`  
Output: `false`

Example 4:  
Input: `s = "([])"`  
Output: `true`

Example 5:  
Input: `s = "([)]"`  
Output: `false`

## Solution
We are told that $1 \le \text{s.length} \le 10^{4}$ and that `s` consists of parentheses only `'()[]{}'`.

This problem seems like the perfect fit for the **stack structure**, since each opening parenthesis must be closed by the same type of parenthesis, in the correct order.

The algorithm uses a **stack** `parentheses` to keep track of the parentheses encountered as I process the input string `s` from *left-to-right*.

 - I first handle the *opening parentheses* by *pushing* them onto the stack.
 - If the stack is *empty*, this means that there is a *missing opening parenthesis*, so I return `false` as the input is not valid. 
 - Otherwise, I handle the *closing parentheses* by checking if the current closing parenthesis matches the type used that is at the *top* of the stack. If they do not match, I return `false` as the input is not valid. Otherwise, I move to the next iteration.
 - Once I process the entire input string `s`, I can return the boolean value depending on whether the stack is empty or not.
 
    - If the stack is *empty*, this means that *every opening parenthesis* found a matching *closing parenthesis* in the correct order. Therefore, I return `true` as the input is valid.
    - If the stack is **not** *empty*, then there was some *parenthesis* left unaccounted for, so I return `false`.

### Pseudocode    

```cpp
bool isValid(string s) {
        
    // initialize stack structure for processing parentheses
    stack<char> parentheses;

    // loop through 's' in left-to-right order
    for (char c : s) {

        // handle opening parentheses
        if (c == '(' || c == '[' || c == '{') {
            parentheses.push(c);
        }
        else { // if the stack is empty, the input is not valid
            if (parentheses.empty()) {
                return false;
            }
            
            // handle closing parentheses by checking if their type match
            char openingParenthesis = parentheses.top();

            // if they match, pop from stack and continue
            if ((c == ')' && openingParenthesis == '(') || 
                (c == ']' && openingParenthesis == '[') || 
                (c == '}' && openingParenthesis == '{')) {
                parentheses.pop();
            }
            else { // if they did not match, the input is not valid
                return false;
            }
        }
    }
    // after processing the entire input string, if the stack is empty, then the input was valid
    return parentheses.empty();
}
```

#### Complexity

 * Assuming the input string `s` contains $n$ parentheses. The algorithm performs a linear scan and, therefore, the total **time complexity** is $\mathcal{O}(n)$.

 * We allocate a *stack* to store all the parentheses. In the worst case, the entire input string is made up solely of *opening parentheses*. Therefore, in the worst case, the total **space complexity** is $\mathcal{O}(n)$.

### Terminal Output

Tests from *ValidParentheses.cpp* in `main.()`:

```text
Input string: ()
Output: valid

Input string: ()[]{}
Output: valid

Input string: (]
Output: NOT valid

Input string: ([])
Output: valid

Input string: ([)]
Output: NOT valid

Input string: (([{([{}])}]))
Output: valid

Input string: {{[[((])]]}}
Output: NOT valid
```
