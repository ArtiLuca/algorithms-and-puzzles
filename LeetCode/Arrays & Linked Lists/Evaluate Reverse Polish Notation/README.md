# Evaluate Reverse Polish Notation

Problem: [LeetCode](https://leetcode.com/problems/evaluate-reverse-polish-notation/description/)

You are given an array of strings `tokens` that represents an arithmetic expression in a **Reverse Polish Notation**.

Evaluate the expression. Return *an integer that represents the value of the expression*.

Note that:

 - The valid operators are `'+'`, `'-'`, `'*'`, and `'/'`.
 - Each operand may be an integer or another expression.
 - The division between two integers always **truncates toward zero**.
 - There will not be any division by zero.
 - The input represents a valid arithmetic expression in a reverse polish notation.
 - The answer and all the intermediate calculations can be represented in a **32-bit** integer.
 

Example 1:  
Input: `tokens = ["2","1","+","3","*"]`  
Output: 9  
Explanation: $((2+1) \times 3) = 9$  

Example 2:  
Input: `tokens = ["4","13","5","/","+"]`  
Output: 6  
Explanation: $(4 + (13 \div 5)) = 6$  

Example 3:  
Input: `tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]`  
Output: 22  
Explanation: 

$$
((10 \times (6 \div ((9+3) \times -11))) + 17) + 5 \\ 
= ((10 \times (6 \div (12 * -11))) + 17) + 5 \\ 
= ((10 \times (6 \div -132)) + 17) + 5 \\ 
= ((10 \times 0) + 17) + 5 \\ 
= (0 + 17) + 5 \\ 
= 17 + 5 = 22
$$

## Solution
We are told that $1 \le \text{tokens.length} \le 10^{4}$ and that `tokens[i]` is either an operator: `"+"`, `"-"`, `"*"`, or `"/"`, or an integer in the range $[-200, 200]$.

I read up on **Reverse Polish Notation** (or **RPN**) online. It is also known as *postfix notation*, since *operators* follow their *operand*.  
For example, when adding the numbers 3 and 4: 

- Using the "conventional notation" this would be: $3 \text{ + } 4$. 
- Using **Reverse Polish Notation** it would instead be: $34 \text{ +}$.

I initially had trouble picturing this in my head, but then found the following example: $3 - 4 + 5$ (which is in the "conventional notation"). In **RPN** this would instead be: $34 \text{ - } 5 \text{+}$ and would be evaluated like this:

$34 \ \text{-} \ 5 \text{+} \ = \ (\text{-}1) \ 5 \text{+} \ = \ 4$

This example helped me understand how, in **Reverse Polish Notation**, an *operator* always applies to the two most recently seen *operands*. This is why using a **stack structure** is useful to preserve this *left-to-right* order when evaluating the expression.

The idea for the algorithm is to:

 - Allocate a **stack structure** to hold each token and then iterate through `tokens` to evaluate the expression.
 - Each time we find an *operand*, we **push** it onto the stack after converting it to its corresponding numerical value. 
 - Each time we find an *operator* we **pop** the two *operands* at the **top** of the stack and perform the arithmetic operation.
    - In particular, when performing an arithmetic operation $num1 \ op \ num2$, the *first* operand we pop from the stack is $num2$, while the second one is $num1$. 

 - We then **push** the result of the given arithmetic operation back onto the stack.

At the end of the algorithm we return the **top** of the **stack**, which contains the solution to the evaluated expression.

### Pseudocode

```cpp
int evalRPN(vector<string>& tokens) {

    // allocate stack structure for evaluating expression
    stack<int> stackRPN;

    // iterate through given expression
    for (const string& ch : tokens) {

        // if we find an operator, we pop two operands
        if (ch == "+" || ch == "-" || ch == "*" || ch == "/") {

            int op1 = stackRPN.top(); stackRPN.pop();
            int op2 = stackRPN.top(); stackRPN.pop();
            int result;

            // perform arithmetic operation, using left-to-right order 
            if (ch == "+") { result = op2 + op1; }
            else if (ch == "-") { result = op2 - op1; }
            else if (ch == "*") { result = op2 * op1; }
            else if (ch == "/") { result = op2 / op1; }

            // and push the result onto the stack
            stackRPN.push(result);
        }
        // if we find an operand
        else {
            // we convert to integer and push it onto the stack
            int num = std::stoi(ch);
            stackRPN.push(num);
        }
    }
    // once we evaluate each token, the top of the stack contains the result
    return stackRPN.top();
}
```

#### Complexity

 * Assuming there are $n$ tokens in the vector `tokens`, and that the operations performed on the **stack** structure (*push*, *pop*,*top*) cost $\mathcal{O}(1)$ on average. The algorithm performs a linear scan, therefore the total **time complexity** is $\mathcal{O}(n)$.
 
 * The algorithm uses $\mathcal{O}(n)$ *auxiliary space* due to the **stack** structure. Therefore, the total **space complexity** is $\mathcal{O}(n)$ (in the worst case).
 
