# Longest Palindromic Subsequence

Problem: [LeetCode](https://leetcode.com/problems/longest-palindromic-subsequence/description/)

Given a string `s`, find the *longest palindromic* ***subsequence's*** *length in* `s`.

A **subsequence** is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

Example 1:  
Input: `s = "bbbab"`  
Output: 4  
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:  
Input: `s = "cbbd"`  
Output: 2  
Explanation: One possible longest palindromic subsequence is "bb".

## Solution 
We are told that $1 \le \text{s.length} \le 1000$ and that `s` consists only of lowercase English letters.

I decided to use a **Dynamic Programming** approach for implementing a solution to this problem.

I defined the problem more generally by defining a *recursive characterization* for computing the value $\ell_{i,j}$, which represents the length of the *longest palindromic subsequence* in the interval $s_i \dots s_j$. In particular, the length of the interval $s_i \dots s_j$ is given by $len = j - i + 1$.

 - If $i > j$, then this means the subsequence $s_i \dots s_j$ is an *empty subsequence*, which is palindromic by definition. In this case,  $\ell_{i,j} = 0$.

 - If $i=j$, then the subsequence $s_i \dots s_j$ is made up by only one character, which is also palindromic by definition. In this case, $\ell_{i,j} = 1$.

 - If $i < j$, then the subsequence $s_i \dots s_j$ is made up of at least two characters. Therefore, I compare the character at the start $s_i$ with the character at the end $s_j$.

    - If $s_i = s_j$, this means I can use these two characters to **extend** the *longest palindromic subsequence* found within the smaller *internal* interval $s_{i+1} \dots s_{j-1}$. In this case, $\ell_{i,j} = 2 + \ell_{i+1,j-1}$.

    - If $s_i \ne s_j$, then I have to decide which character to keep in order to achieve the *longest palindromic subsequence*. In this case, $\ell_{i,j} = \max(\ell_{i+1,j}, \ell_{i,j-1})$

I can use these observations to define a recurrence for computing the value of $\ell_{i,j}$:

$$
\ell_{i,j}=
\begin{cases}
0 & \text{if } i > j, \\
1 & \text{if } i = j, \\
2 + \ell_{i+1,j-1} & \text{if } i < j \text{ and } s_i = s_j, \\
\max\{\ell_{i+1,j},\ell_{i,j-1}\} & \text{if } i < j \text{ and } s_i \ne s_j.
\end{cases}
$$

I decided to implement a *bottom-up* solution in which I consider each interval $s_i \dots s_j$ of increasing length $len = 2 \dots n$. I use a vector `lengths` to store the lengths $\ell_{i,j}$ found as the algorithm progresses. 

### Pseudocode

```cpp
int longestPalindromeSubseq(string s) {

    int n = s.length();

    // guard
    if (n == 0) {
        return 0;
    }

    // allocate vector for storing lengths found
    vector<vector<int>> lengths(n+1, vector<int>(n+1, 0));
    
    // handle base cases
    for (int i = 1; i <= n; i++) {

        // empty subsequence
        lengths[i][i-1] = 0;
        // single character subsequence
        lengths[i][i] = 1;
    }

    // fill table calculating intervals of increasing length
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            // if first and last characters match
            if (s[i - 1] == s[j - 1]) {
                lengths[i][j] = 2 + lengths[i+1][j-1];
            }

            // otherwise, choose option that maximizes solution
            else {
                lengths[i][j] = std::max(lengths[i+1][j], lengths[i][j-1]);
            }
        }
    }
    // the length of the longest palindromic subsequence is found in lengths[1][n]
    return lengths[1][n];
}
```

#### Complexity

 * Assuming there are $n$ characters in the input string. The nested loops in the algorithm iterate from $len=2 \dots n$ and from $i=1 \dots n-len+1$. This can be approximated to roughly $\frac{n \times (n-1)}{2} \approx n^2$. Therefore, the total **time complexity** is quadratic: $\mathcal{O}(n^2)$.

 * The algorithm uses the vector `lengths`, which has size $(n+1) \times (n+1)$. Therefore, the total **space complexity** is also quadratic: $\mathcal{O}(n^2)$.

### Terminal Output
Tests from *LongestPalindromicSubsequence.cpp* in `main()`:

```text
----------------------------------------
Example 0:
  Input String   : bbbab (Length: 5)
  Expected       : (e.g., "bbbb")
  Calculated Max : 4
----------------------------------------
Example 1:
  Input String   : cbbd (Length: 4)
  Expected       : (e.g., "bb")
  Calculated Max : 2
----------------------------------------
Example 2:
  Input String   : abacdfgaba (Length: 10)
  Expected       : (e.g., "ababa")
  Calculated Max : 7
----------------------------------------
Example 3:
  Input String   : aaaaabaaaaa (Length: 11)
  Expected       : (e.g., "aaaaabaaaaa")
  Calculated Max : 11
----------------------------------------
Example 4:
  Input String   : abcdefg (Length: 7)
  Expected       : (e.g., "a")
  Calculated Max : 1
----------------------------------------
Example 5:
  Input String   : leetcodecasesedocteel (Length: 21)
  Expected       : (e.g., "leetcodeseocteel")
  Calculated Max : 19
----------------------------------------
Example 6:
  Input String   : xyzxyzxyzxyzxyz (Length: 15)
  Expected       : (e.g., "xyzyx")
  Calculated Max : 9
----------------------------------------
Example 7:
  Input String   : paddPADUAmelwlePADUAddapxyzxyzxyzxyz (Length: 36)
  Expected       : (e.g., "paddPADUAmellePADUAddap")
  Calculated Max : 19
----------------------------------------
```
