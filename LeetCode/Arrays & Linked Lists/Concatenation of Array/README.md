# Concatenation of Array

Problem: [LeetCode](https://leetcode.com/problems/concatenation-of-array/)

Given an integer array `nums` of length `n`, you want to create an array `ans` of length `2n` where `ans[i] == nums[i]` and `ans[i + n] == nums[i]` for $0 \le i < n$ (**0-indexed**).

Specifically, `ans` is the **concatenation** of two `nums` arrays.

Return the *array* `ans`.

Example 1:

Input: $nums = [1,2,1]$  
Output: $[1,2,1,1,2,1]$  
Explanation: The array ans is formed as follows:  
- $ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]$
- $ans = [1,2,1,1,2,1]$

Example 2:

Input: $nums = [1,3,2,1]$  
Output: $[1,3,2,1,1,3,2,1]$  
Explanation: The array ans is formed as follows:  
- $ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]$
- $ans = [1,3,2,1,1,3,2,1]$


## Solution
We are told that $n = \text{nums.length}$, $1 \le n \le 1000$, and $1 \le \text{nums[i]} \le 1000$.  

The first idea that came to mind was creating a vector `ans` of size **2n** in order to hold the **concatenation** of the two `nums` vectors. We can use a single loop to fill both *equal* halves of `ans` ($ans[0 \dots n-1]$ and $ans[n \dots 2n-1]$) before returning it as the result.

#### Pseudocode

```cpp
vector<int> getConcatenation(vector<int>& nums) {

    int n = nums.size();

    // create new vector, doubled in size
    vector<int> ans(2*n); 

    // loop once to fill both equal halves
    for (int i = 0; i < n; i++) {
        ans[i] = nums[i];
        ans[n+i] = nums[i];
    }

    return ans;
}
```

#### Complexity
Assuming `nums` contains $n$ elements, populating the newly created `ans` vector takes $n$ iterations. Therefore, the total **time complexity** is $\mathcal{O}(n)$.

Since we allocate a *new* vector of size $2n$, the total **space complexity** is also $\mathcal{O}(n)$.


