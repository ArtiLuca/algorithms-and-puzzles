# Merge Sorted Array

Problem: [LeetCode](https://leetcode.com/problems/merge-sorted-array/description/)

You are given two integer arrays `nums1` and `nums2`, sorted in **non-decreasing order**, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

**Merge** `nums1` and `nums2` into a single array sorted in **non-decreasing order**.

The final sorted array should not be returned by the function, but instead be *stored inside* the array `nums1`. To accommodate this, `nums1` has a length of $m + n$, where the first `m` elements denote the elements that should be merged, and the last `n` elements are set to `0` and should be ignored. `nums2` has a length of `n`.

Example 1:  
Input: $nums1 = [1,2,3,0,0,0]$, $m = 3$, $nums2 = [2,5,6]$, $n = 3$  
Output: $[1,2,2,3,5,6]$  
Explanation: The arrays we are merging are $[1,2,3]$ and $[2,5,6]$.  
The result of the merge is $[\underline{1},\underline{2},2,\underline{3},5,6]$ with the underlined elements coming from `nums1`.


Example 2:  
Input: $nums1 = [1]$, $m = 1$, $nums2 = []$, $n = 0$  
Output: $[1]$  
Explanation: The arrays we are merging are $[1]$ and $[]$. The result of the merge is $[1]$.


Example 3:  
Input: $nums1 = [0]$, $m = 0$, $nums2 = [1]$, $n = 1$  
Output: $[1]$  
Explanation: The arrays we are merging are $[]$ and $[1]$. The result of the merge is $[1]$.  
Note that because $m = 0$, there are no elements in `nums1`. The `0` is only there to ensure the merge result can fit in `nums1`.

## Solution
We are told that:  
 - $\text{nums1.length} == m + n$
 - $\text{nums2.length} == n$
 - $0 \le m$, $n \le 200$
 - $1 \le m + n \le 200$
 - $-10^{9} \le \text{nums1[i]}$, $\text{nums2[j]} \le 10^{9}$


We are also asked as a follow-up question if we can come up with an algorithm that runs in $\mathcal{O}(m + n)$ time.

Since `nums1` and `nums2` are both sorted in increasing order, we can use this to our advantage. Since `nums1` is large enough to contain both `nums1` and `nums2` we can implement the merging operation by populating `nums1` from **right to left**, always inserting the largest element of `nums1` and `nums2` that are yet to be merged. 

We can use two *index trackers* `i` and `j` initially set to `i=m-1` and `j=n-1` and then iterate `nums1`  
for index $k = m + n - 1 \dots 0$.  

At each step we insert into `nums1[k]` where:

 - if no elements are left in `nums2` ($j < 0$), then we don't need to do anything. The remaining elements in nums1 are already in their correct sorted positions, so we can break from the loop. 
 - if no elements are left in `nums1` ($i<0$) or the current element in `nums2` is larger the current one in `nums1` then we insert `nums2[j]` into `nums1[k]` and decrease the index tracker `j` by 1. 
 - otherwise, if `nums1[i]` contains an element that is larger (or equal) to the current one of `nums2`, then we simply insert `nums1[i]` into `nums1[k]` and decrease the index tracker `i` by 1.

The loop stops when `k < 0`, at which point `nums1` contains the merged elements of `nums1` and `nums2` sorted in increasing order.  
This works since we insert the largest element from **right to left** in `nums1` and we are guaranteed that `nums1` is sufficiently large to contain the merged result, we always insert the largest current element between `nums1` and `nums2` (with duplicate values given higher priority in `nums1`).  


#### Pseudocode

```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

    // index trackers 
    int i = m - 1; // m = nums1.length();
    int j = n - 1; // n = nums2.length();

    for (int k = m + n - 1; k >= 0; k--) {

        // if no elements from nums2, nums1 is already sorted
        if (j < 0) {
            // so we can break from the loop
            break;
        } 

        // if no elements from nums1 remain or nums2 contains the largest
        if (i < 0 || nums2[j] > nums1[i]) {
            nums1[k] = nums2[j];
            j--;
        }

        // otherwise, we insert from nums1
        else {
            nums1[k] = nums1[i];
            i--;
        }
    }
}
```

#### Complexity
We scan `nums1` from right to left, meaning we perform $m+n$ iterations, performing operations that require constant cost at each step.  
Therefore, the total **time complexity** is $\mathcal{O}(m+n)$.

Since both `nums1` and `nums2` are passed by reference, the total **space complexity** is constant $\mathcal{O}(1)$.