# Set Mismatch

Problem: [LeetCode](https://leetcode.com/problems/set-mismatch/)

You have a set of integers `s`, which originally contains all the numbers from `1` to `n`. Unfortunately, due to some error, one of the numbers in `s` got duplicated to another number in the set, which results in **repetition of one** number and **loss of another number**.

You are given an integer array `nums` representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return *them in the form of an array.*

Example 1:  
Input: $nums = [1,2,2,4]$  
Output: $[2,3]$

Example 2:  
Input: $nums = [1,1]$  
Output: $[1,2]$

## Solution
We are told that $2 \le \text{nums.length} \le 10^{4}$ and that $1 \le \text{nums[i]} \le 10^{4}$.

For this problem, we do not know whether the vector `nums` is *sorted* or not. We only know that there are $n$ elements $1 \dots n$ and that one of them is missing, creating a *duplicate*.

For this problem, I thought of 4 different possible solutions, each with its pros and cons:

1. **Sorting and Sequence Checking**
2. **Using a Hash Set**
3. **Cyclic Sorting**
4. **Using the Sum and Sum of Squares**

**Note**: In each approach, I assume that the vector `nums` contains $n$ elements.

### Approach 1: Sorting and Sequence Checking

The first one is the most "intuitive", but is also the least efficient  out of all of them, in terms of time complexity. The idea is to first **sort** the vector `nums` in increasing order and then do a single linear scan to find the `duplicate` number and the `expected` number. Initially, we use `duplicate = -1` and `expected = 1`, and then scan the vector `nums` from $i=1 \dots n$: 

 - if `nums[i] == nums[i-1]`, then we found the `duplicate`.
 - if `nums[i] == expected`, we increment `expected`.
 - if `nums[i] > expected`, the current `expected` value is the missing number.

```cpp
vector<int> findErrorNums(vector<int>& nums) {

    // sort nums in increasing order
    sort(nums.begin(), nums.end());

    // set initial variables
    int duplicate = -1;
    int expected = 1;

    for (int i = 0; i < (int)nums.size(); i++) {

        // if past first, we check for a duplicate
        if (i > 0 && nums[i] == nums[i-1]) {
            duplicate = nums[i];
        }
        // if we find the expected number, we increment to the next one in the sequence
        else if (nums[i] == expected) {
            expected++;
        }
    }

    // once the loop finished, expected contains the missing number
    return {duplicate, expected};
}
``` 

This approach is probably the most "intuitive" but also the one with the worst total **time complexity**, which is given by the initial *sorting* phase, which has cost $\mathcal{O}(n \log n)$. We then perform a linear scan of cost $\mathcal{O}(n)$, which is absorbed by the *sorting* cost.

The total **space complexity** is $\mathcal{O}(1)$ since we do not use any extra auxiliary space.

---

### Approach 2: Hash Set: Using a Hash Set
We can obtain a more efficient time complexity using a **hash set**, at the expense of using a costlier space complexity.

The idea is to perform two linear scans using a `std::unordered_set<int> seen` object. In the first scan, we populate the set by *inserting* each element found in `nums`. Since there is a *duplicate*, when we try to insert it into an `unordered_set`, the operation will fail. This gives us the `duplicate` number. 

Once we have populated the set, we can perform a second scan to check the numbers in `nums` against the sequence $1 \dots n$. We inspect the set `seen`, eventually not being able to find one. This gives us the `missing` number.

 ```cpp
 vector<int> findErrorNums(vector<int>& nums) {

    // create hash set and set initial expected/duplicate placeholder values
    unordered_set<int> seen;
    int duplicate = -1;
    int missing = 1;

    // populate the hash set and find duplicate number
    for (int num : nums) {

        // if an insertion fails, we found the duplicate number
        if (!seen.insert(num).second) {
            duplicate = num;
        }
    }

    // after populating the hash set, we check from 1 to n to find the missing number
    for (int i = 1; i <= (int)nums.size(); i++) {
        if (seen.find(i) == seen.end()) {
            missing = i;
            break;
        }
    }

    return {duplicate, missing};
 }
 ```

We perform two linear scans, with the operations performed on the **hash set** having a cost of $\mathcal{O}(1)$ on average. Therefore, the total **time complexity** is $\mathcal{O}(n)$.

Although the time complexity is better than the previous approach, we now use a **hash set**, which means we now use a total **space complexity** of $\mathcal{O}(n)$ to store it.

---

### Approach 3: Cyclic Sorting
It is possible to obtain a solution that uses no auxiliary space in linear time. The idea is to *sort* the vector `nums` *in-place* in a single pass. This can be done by observing that, since the vector `nums` contains the numbers strictly from $1 \dots n$, the array's indices can be used as a *hash map*. 

This means that for each number $x$ in $1 \dots n$, we can iterate the vector `nums` and place $x$ in its correct *0-indexed* position $x-1$. This *cyclic sorting* continues swapping elements until every number $x$ is at its correct index or the `duplicate` number is found.  

After *sorting* the vector, we use a second linear scan to find the `missing` number by checking for the condition `nums[i] != i+1`. Once this happens, we have found the `duplicate` number, and the `missing` number is simply `i+1`. 

```cpp
vector<int> findErrorNums(vector<int>& nums) {

    int n = nums.size();

    // swap in-place to put each number in correct 0-indexed position
    for (int i = 0; i < n; i++) {
        while (nums[i] != nums[nums[i] - 1]) {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }

    // find index of number that does not match expected value
    for (int i = 0; i < n; i++) {
        if (nums[i] != i+1) {
            return {nums[i], i+1};
        }
    }

    // otherwise...
    return {};
}
```

This approach is a bit like the *best of both worlds* from the first and second, since we obtain a total **time complexity** of $\mathcal{O}(n)$ while at the same time also a total **space complexity** of $\mathcal{O}(1)$.

---

### Approach 4: Using the Sum and Sum of Squares

One last approach that is as efficient as the third one does not modify the original vector `nums` and uses mathematical properties to implement the solution. It is definitely the *least intuitive* one and also, for me, the *less likely* to be actually implemented in a real-world scenario (as opposed to the second approach).  

Let $x$ be the `duplicate` number and `y` be `missing` number. If we subtract the *actual sum* of the vector from the *expected sum*:

$$
\sum_{i=1}^{n} (i) - \sum_{\text{nums[i]}}^{\text{nums[n]}} (\text{nums[i]}) = y - x
$$ 

Therefore, if we subtract the *actual sum of squares* from the *expected sum of squares*, the difference is: $y^{2} - x^{2}$.

If we expand this: $y^{2} - x^{2} = (y-x)(y+x)$, we can *divide the squares difference* $\text{sumDiffSq}$ by the *sum difference* $\text{sumDiff}$ to get $\text{sumXY} = y+x$.

Once we have $\text{sumXY} = y+x$, we can find: 

 - `missing` = $\frac{\text{(sumDiff + sumXY)}}{2}$
  
 - `duplicate` = $sumXY - missing$

```cpp
vector<int> findErrorNums(vector<int>& nums) {

    long long n = nums.size();

    // using Gauss summation to get expected and squared sums
    long long expectedSum = n * (n+1) / 2;
    long long expectedSumSquared = n * (n+1) * (2 * n + 1) / 6;

    // find the actual and expected sums
    long long actualSum = 0;
    long long actualSumSquared = 0;

    // iterate vector to compute sums
    for (long long num : nums) {
        actualSum += num;
        actualSumSquared += num * num;
    }

    // compute difference of sums
    long long diff1 = expectedSum - actualSum;
    // compute difference of squared sums
    long long diff2 = expectedSumSquared - actualSumSquared;

    // divide differences to find sum of missing and duplicate number
    long long sumXY = diff2 / diff1;

    // compute missing number
    long long missing = (diff1 + sumXY) / 2;
    // compute duplicate number
    long long duplicate = sumXY - missing;

    // return them
    return {(int)duplicate, (int)missing};
}
```

This last approach, although less intuitive, is as efficient as the third one. The total **time complexity** here is also $\mathcal{O}(n)$, as is the total **space complexity**, which here is also $\mathcal{O}(1)$.

