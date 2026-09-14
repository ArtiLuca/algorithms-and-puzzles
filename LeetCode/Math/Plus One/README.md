# Plus One

Problem: [LeetCode](https://leetcode.com/problems/plus-one/description/)

You are given a **large integer** represented as an integer array `digits`, where each `digits[i]` is the *i-th* digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the *resulting array of digits*.

Example 1:

Input: `digits = [1,2,3]`  
Output: `[1,2,4]`  
Explanation: The array represents the integer 123. Incrementing by one gives 123 + 1 = 124.  
Thus, the result should be `[1,2,4]`.

Example 2:

Input: digits = `[4,3,2,1]`  
Output: `[4,3,2,2]`  
Explanation: The array represents the integer 4321. Incrementing by one gives 4321 + 1 = 4322.  
Thus, the result should be `[4,3,2,2]`.

Example 3:

Input: digits = `[9]`  
Output: `[1,0]`  
Explanation: The array represents the integer 9. Incrementing by one gives 9 + 1 = 10.  
Thus, the result should be `[1,0]`.

## Solution
We are told that $1 \le \text{digits.length} \le 100$, that $0 \le \text{digits[i]} \le 9$, and that `digits` does not contain any leading 0s.

We are only told that `digits` represents a **large integer**, so it's safe to assume that trying to convert the array into its corresponding numerical value by repeated multiplication could cause *integer overflow*. 

What we can do instead is iterate through the array from *right to left*, starting from `digits[i-1]`, with $i = \text{digits.size} \dots 0$. At each iteration, we increment the current digit by 1. If the resulting digit is $\le 9$ after the increment, we can return `digits` as we have successfully incremented it by 1. 

However, since the digits may only be $0 \dots 9$, if the current digit becomes $> 9$ after the increment, we must then set the current digit to 0 and  *carry over* to the next digit in `digits`.

If we loop through the entire array `digits`, then this means that all digits found were 9 and, in this particular case, to increment `digits` by 1 we must **insert** a leading $1$. We can do this using the `std::vector::insert` function or by simply setting `digits[0]` to $1$ and then **pushing** a trailing $0$ into `digits`. This second option has the benefit of not having to **resize** `digits` before performing the insertion.

```cpp
vector<int> plusOne(vector<int>& digits) {

    int n = (int)digits.size();
    
    // loop through digits from right to left
    for (int i = n - 1; i >= 0;  i--) {

        // increment current digit by 1
        digits[i]++;

        // after incrementing, if no carry is needed, we are done
        if (digits[i] < 10) {
            return digits;
        }

        // otherwise, we set current digit to 0, and carry over to next iteration
        digits[i] = 0;
    }

    // if we reach this point, then all elements were 9, so we must add a leading 1
    digits[0] = 1;
    digits.push_back(0);
    return digits;
}
```

#### Complexity
Assuming `digits` contains $n$ elements, we perform at most $n$ iterations, performing constant work at each step. Therefore, the total **time complexity** in the worst case is $\mathcal{O}(n)$. However, due to early terminations, this is not usually the case.

The total **space complexity** is $\mathcal{O}(1)$ since we operate *in place* and even in the worst case of all digits being $9$, the single call to `push_back` only adds an extra constant $\mathcal{O}(1)$ in terms of total space used.
