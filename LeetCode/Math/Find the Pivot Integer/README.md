# Find the Pivot Integer

Problem: [LeetCode](https://leetcode.com/problems/find-the-pivot-integer/)

Given a positive integer `n`, find the **pivot integer** `x` such that:

  - The sum of all elements between `1` and `x` inclusively equals the sum of all elements between `x` and `n` inclusively.
  - Return *the pivot integer* `x`. If no such integer exists, return `-1`. It is guaranteed that there will be at most one pivot index for the given input.

Example 1:

Input: $n = 8$  
Output: $6$  
Explanation: 6 is the pivot integer since: $1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21$.

Example 2:

Input: $n = 1$  
Output: $1$  
Explanation: $1$ is the pivot integer since: $1 = 1$.

Example 3:

Input: $n = 4$  
Output: $-1$  
Explanation: It can be proved that no such integer exist.

## Solution
We are told that $1 \le n \le 1000$ and that it is *guaranteed* that the given input will have at most **one pivot index**.

The *immediate* approach that came to mind was performing a linear scan and comparing the **left sum** with the **right sum**. To do this, we would:

 1. Calculate the `totalSum` of 1 to n. Using the **Gauss summation**, this is equivalent to: $\frac{n \times (n+1)}{2}$. 

 2. Keep a running `leftSum` starting at 0.
 3. For each number i from 1 to n, we then:
    - Add $i$ to `leftSum`.
    - Calculate the `rightSum`, which includes i to n: `totalSum - leftSum + i`.
    - If at the end `leftSum == rightSum`, we return i.
 4. Otherwise, we return -1. 

#### Pseudocode

```cpp
int pivotInteger(int n) {

    // compute total sum with Gauss summation
    int totalSum = n * (n + 1) / 2;
    int leftSum = 0;

    // for each number i from 1 to n
    for (int i = 1; i <= n; i++) {

        // compute leftSum and rightSum
        leftSum += i;
        int rightSum = totalSum - leftSum + i;

        // if they match, we found the pivot integer
        if (leftSum == rightSum) {
            return i;
        }
    }

    // otherwise the pivot integer cannot be found
    return -1;
}
```

#### Complexity
Using this approach, the total **time complexity** is $\mathcal{O}(n)$, since we iterate the entire sequence in the worst case.

The total **space complexity** is $\mathcal{O}(1)$.

---

However, we can achieve a solution in constant time if we make the following observation. We want to find the element at index `x` such that the sum of 1 to x (inclusive) is equal to the sum of x to n (inclusive).

Using the **Gauss summation**, we can express the sum of x to n as the sum of 1 to n, minus the sum of 1 to x, meaning:  

$$
\sum_{i=x}^{n}(i) = \sum_{i=1}^{n}(i) - \sum_{i=1}^{x-1}(i)
$$

If we expand the *summations*, we have:  

$$
\frac{x(x+1)}{2} = \frac{n(n+1)}{2} - \frac{(x-1)x}{2} \\ 
= \frac{n(n+1)}{2} - \frac{x^{2}-x}{2}
$$  

Multiplying by 2 and then simplifying we get: 

$$
x(x+1) = n(n+1) - x(x-1) \\ 
= x^{2} + x = n^{2} + n - (x^{2} - x)
$$

If we cancel the common terms, move the others to the left, and then divide by 2, we have: 

$$
2x^{2} = n(n+1) \\ 
= x^2 = \frac{n(n+1)}{2} 
$$

This means that the **pivot integer** `x` is equal to the **square root** of the *total sum from 1 to n*, meaning:

$$
x = \sqrt{\frac{n(n+1)}{2}}
$$  

Or simply put: $\sqrt{\text{totalSum}}$.

This makes the solution to the problem much more straightforward.

#### Pseudocode

```cpp
int pivotInteger(int n) {

    // compute total sum from 1 to n
    int totalSum = n * (n + 1) / 2;

    // find the square root of the total sum
    int x = std::sqrt(totalSum);
    // if x squared is equal to the total sum
    if (x * x == totalSum) {
        // we found our pivot integer
        return x;
    }

    // otherwise, it was not found
    return -1;
}
```

#### Complexity
Since the `sqrt` operation has a constant cost, the total **time complexity** in this case is $\mathcal{O}(1)$, and the total **space complexity** remains $\mathcal{O}(1)$.

