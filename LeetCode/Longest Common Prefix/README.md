# Longest Common Prefix

Problem: [LeetCode](https://leetcode.com/problems/longest-common-prefix/description/)

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

```text
Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
```

## Solution
We are told that:
 - $1 \le \text{ strs.length } \le 200$.
 - $0 \le \text{ strs[i].length } \le 200$.
 - `strs[i]` consists of only lowercase English letters if it is non-empty.

A first solution idea is to simply scan the entire set of strings from $i=0 \dots 200$ while using the index `i` as our *position tracker*.  
If there are no strings or the first one is empty `strs.empty() || strs[0].empty()`, we simply return `""`.  
Otherwise, we loop through the first string `strs[0]` and inspect each character `c= strs[0][i]`.  
We then loop all remaining strings, where we return the result `strs[0].substr(0,i)` if:  
 - the string is empty `strs[j].empty()`.
 - the string is too short `i >= strs[j].size()`.
 - we find a mismatch `strs[j][i] != c`.

Otherwise, we continue to the next position, until eventually returning the longest common prefix found as `strs[0].substr(0,i)` or `strs[0]` if the first string itself is in its entirety the longest common prefix.

#### Pseudocode

```cpp
string longestCommonPrefix(vector<string>& strs) {

      if (strs.empty() || strs[0].empty()) {
          return "";
      }

      int n = strs.size();

      for (int i = 0; i < (int)strs[0].length(); i++) {

          char c = strs[0][i];

          for (int j = 1; j < n; j++) {

              // if we find empty string
              if (strs[j].empty()) {
                  return strs[0].substr(0,i);
              }

              // if we find string that is too short
              if (i >= (int)strs[j].length()) {
                  return strs[0].substr(0,i);
              }

              // if we find mismatch
              if (strs[j][i] != c) {
                    return strs[0].substr(0,i);
              }
          }
      }

      // otherwise, entire first string is result
      return strs[0];
}
```

#### Complexity
If we have $n$ strings, each of length at the most $m$, then in the worst case scenario we have a **time complexity** of $\Theta(n \times m)$.

Since the vector of strings `strs` is passed by reference, the total **space complexity** is constant $\Theta(1)$.
