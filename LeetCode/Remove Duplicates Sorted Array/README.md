# Remove Duplicates from Sorted Array

Problem: [LeetCode](https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/)

Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates *in-place* such that each unique element appears only **once**.  
The **relative order** of the elements should be kept the **same**.

Consider the number of unique elements in `nums` to be `k`​​​​​​​​​​​​​​. After removing duplicates, return the number of unique elements `k`.

The first `k` elements of `nums` should contain the unique numbers in **sorted order**. The remaining elements beyond index `k - 1` can be ignored.

*Custom Judge*:  
The judge will test your solution with the following code:

```cpp
int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```  

If all assertions pass, then your solution will be accepted.

## Solution

We are told that $1 \le \text{nums.length} \le 3 \times 10^{4}$, $-100 \le \text{nums[i]} \le 100, and that `nums` is sorted in **non-decreasing** order.

We can use a *two-pointer* technique of sorts to scan the entire vector and overwrite any duplicate values found, while keeping  
a counter `k` that indicates the number of distinct elements in the final vector.

We can scan the vector `nums` starting from the second element with `k=1` initially.  
At each step we check if the current value is different from the preceding value.  
If `nums[i]` $\ne$ `nums[i-1]` we can then set `nums[k]` to `nums[i]` and increment the value of `k`.  
If, however, the two elements are the same then we found a duplicate value, in which case we dont do anything  
and simply *skip* this element.  

After scanning the entire vector, each duplicate value is overwritten and the first $nums[0 \dots k]$ elements correspond to the  
distinct elements in out final vector.

```cpp
int removeDuplicates(vector<int>& nums) {
    
    // guard
    if (nums.empty()) {
        return -1;
    }

    int k = 1;
    for (int i = 1; i < (int)nums.size(); i++) {

        // if distinct value
        if (nums[i] != nums[i-1]) {
            // overwrite
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}
```

#### Complexity
If $n$ is the number of integers in the vector, at each iteration we perform operations with a constant cost $\Theta(1)$.
Therefore, the resulting **time complexity** is linear $\Theta(n)$.

Since the vector `nums` is passed by reference, the **space complexity** (or auxiliary space) needed is constant $\Theta(1)$.

