# Find the Index of the First Occurrence in a String

Problem: [LeetCode](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)

Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

```text
Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.  


Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
```

## Solution

Other than being told that $1 \le \text{haystack.length}$ and that $\text{needle.length } \le 10^{4}$ we are not given any other constraints.
Therefore, the first solution that comes to mind is using the `find` method provided by `std::string`.

Given two strings `s1` and `s2`, the function `s1.find(s2)` looks for `s2` in `s1` and returns the position of the first character of `s2` found in `s1` if the search was successful.
Otherwise, if no match was found, it returns `std::string::npos`.

#### Pseudocode

```cpp
int strStr(string haystack, string needle) {

    if (needle.length() > haystack.length()) {
        return -1;
    }

    size_t firstIndex = haystack.find(needle);
    if (firstIndex != std::string::npos) {
        return firstIndex;
    }
    else {
        return -1;
    }
}
```

#### Complexity
If $n$ is the length of the string `haystack` and $m$ is the length of the string `needle`, the total **time complexity** is $\mathcal{O}(n \times m)$.

Similarly, the **space complexity** is $\mathcal{O}(n + m)$.
