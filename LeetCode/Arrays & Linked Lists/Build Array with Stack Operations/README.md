# Build an Array With Stack Operations

Problem: [LeetCode](https://leetcode.com/problems/build-an-array-with-stack-operations/description/)


You are given an integer array `target` and an integer `n`.

You have an empty stack with the two following operations:

 - **"Push"**: pushes an integer to the top of the stack.
 - **"Pop"**: removes the integer on the top of the stack.
 
 You also have a stream of the integers in the range $[1 \dots n].$

Use the two stack operations to make the numbers in the stack (from the bottom to the top) equal to `target`. You should follow the following rules:

 - If the stream of the integers is not empty, pick the next integer from the stream and push it to the top of the stack.
 - If the stack is not empty, pop the integer at the top of the stack.
 - If, at any moment, the elements in the stack (from the bottom to the top) are equal to target, do not read new integers from the stream and do not do more operations on the stack.

Return the *stack operations* needed to build target following the mentioned rules. If there are multiple valid answers, return **any of them**.

Example 1:

```text
Input: target = [1,3], n = 3
Output: ["Push","Push","Pop","Push"]
Explanation: Initially the stack s is empty. The last element is the top of the stack.
Read 1 from the stream and push it to the stack. s = [1].
Read 2 from the stream and push it to the stack. s = [1,2].
Pop the integer on the top of the stack. s = [1].
Read 3 from the stream and push it to the stack. s = [1,3].
```

Example 2:

```text
Input: target = [1,2,3], n = 3
Output: ["Push","Push","Push"]
Explanation: Initially the stack s is empty. The last element is the top of the stack.
Read 1 from the stream and push it to the stack. s = [1].
Read 2 from the stream and push it to the stack. s = [1,2].
Read 3 from the stream and push it to the stack. s = [1,2,3].
```

Example 3:

```text
Input: target = [1,2], n = 4
Output: ["Push","Push"]
Explanation: Initially the stack s is empty. The last element is the top of the stack.
Read 1 from the stream and push it to the stack. s = [1].
Read 2 from the stream and push it to the stack. s = [1,2].
Since the stack (from the bottom to the top) is equal to target, we stop the stack operations.
The answers that read integer 3 from the stream are not accepted.
```

## Solution
We are told that $1 \le \text{target.length} \le 100$, that $1 \le n \le 100$, that $1 \le \text{target[i]} \le n$, and that `target` is strictly increasing.

The important thing to note is that we are not asked to implement a **stack data structure**, but to simulate the stack operations as **"Push"** and **"Pop"**. The idea is to start from value 1 and go up to n. For every value we find that matches with the input stream, we need a **"Push"** operation. For every value that we find that does not match, we instead need a **"Push"** followed by a **"Pop"** operation. 

 - Since we know that `target` contains numbers from 1 to n, we can use a temporary variable `ind` to act as an index tracker for the input stream `target`. Initially, we set `ind` to 0.
 - We then loop through the **integer stream** for `i` going from 1 to n (*inclusive*), pushing the needed **stack operations** into a vector `vector<string> stackOperations` based on the current value `i` being evaluated. At each iteration:
  
   - If $\text{ind = target.size()}$, then we *break* as we have finished matching all target numbers.
   - If $i < \text{target[ind]}$, we push the operations **"Push"** and **"Pop"** in `stackOperations`.
   - If $i = \text{target[ind]}$, we then increment `ind` by 1 and push the operation **"Push"** in `stackOperations`.


#### Pseudocode

```cpp
vector<string> buildArray(vector<int>& target, int n) {

    // allocate stack operations vector 
    vector<string> stackOperations;
    // set initial index tracker
    int ind = 0;

    // iterate through input stream target
    for (int i = 1; i <= n; i++) {

        // if index tracker matches input stream size, we matched all values
        if (ind == target.size()) {
            break;
        }

        // if value is smaller than target, "Push" and "Pop"
        if (i < target[ind]) {
            stackOperations.push_back("Push");
            stackOperations.push_back("Pop");
        }
        // if value matches target in input stream, we "Push" and increment index tracker
        else if (i == target[ind]) {
            stackOperations.push_back("Push");
            ind++;
        }
    }

    // return stack operations vector found
    return stackOperations;
}
```

#### Complexity

 * We perform a linear scan, with *insert* operations having cost $\mathcal{O}(1)$ on average. Therefore, the total **time complexity** is $\mathcal{O}(n)$.

 * Since we can disregard the allocated return vector in the space complexity, and we don't use any extra *auxiliary space*, the total **space complexity** is $\mathcal{O}(1)$. 

