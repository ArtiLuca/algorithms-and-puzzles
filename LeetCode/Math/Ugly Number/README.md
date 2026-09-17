# Ugly Number

Problem: [LeetCode](https://leetcode.com/problems/ugly-number/)

An **ugly number** is a *positive* integer which does not have a prime factor other than 2, 3, and 5.

Given an integer `n`, return `true` if `n` is an *ugly number*.

Example 1:  
Input: $n = 6$  
Output: `true`  
Explanation: $6 = 2 \times 3$

Example 2:  
Input: $n = 1$  
Output: `true`  
Explanation: 1 has no prime factors.

Example 3:  
Input: $n = 14$  
Output: `false`  
Explanation: 14 is not ugly since it includes the prime factor 7.
 
## Solution
We are told that $-2^{31} \le n \le 2^{31} - 1$

For this problem, I remembered the **Fundamental Theorem of Arithmetic**, which states that *every integer greater than 1 is either a prime number or can be written as a unique product of prime numbers, ignoring the order of the factors*.

We can therefore check if a number `n` is an **ugly number** by first checking if the number is zero or negative. If `n <= 0` we immediately return `false`. Otherwise, we repeatedly keep dividing `n` by one of the *prime factors* $2,3,5$, as long as `n` is perfectly divisible by the given *prime factor*. We do this using three loops, one for each *prime factor*, where the order in which we check them is irrelevant.

After performing all three loops, if `n==1`, we can conclude that `n` is an **ugly number**, so we return `true`. Otherwise, `n` is **not an ugly number**, so we return `false`.

#### Pseudocode

```cpp
class Solution {
public:
    bool isUgly(int n) {
        
        // negative numbers and 0 cannot be ugly 
        if (n <= 0) {
            return false;
        }

        // strip out prime factors     
        while (n % 2 == 0) { n = n / 2; }
        while (n % 3 == 0) { n = n / 3; }
        while (n % 5 == 0) { n = n / 5; }

        // if resulting n is 1, it is an ugly number
        return n == 1;
    }
};
```

#### Complexity
Since the algorithm only performs division operations, we can look at the depth of each division loop. These are similar to the *heights* of *balanced binary trees* and are $\mathcal{O}(\log_{2} n)$, $\mathcal{O}(\log_{3} n)$, and $\mathcal{O}(\log_{5} n)$. Therefore, adding the three costs together yields a total **time complexity** of $\mathcal{O}(\log n)$.

The total **space complexity** is $\mathcal{O}(1)$ since no auxiliary space is needed.
