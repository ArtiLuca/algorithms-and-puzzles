# Longest Palindromic Substring

Problem: [LeetCode](https://leetcode.com/problems/longest-palindromic-substring/description/)

Given a string `s`, return the *longest palindromic substring* in `s`.

Example 1:  
Input: `s = "babad"`  
Output: `"bab"`  
Explanation: "aba" is also a valid answer.

Example 2:  
Input: `s = "cbbd"`  
Output: `"bb"`

## Solution
We are told that $1 \le \text{s.length} \le 1000$ and that `s` consists only of lowercase English letters.

I decided to use a **Dynamic Programming** approach for implementing a solution to this problem.

I defined the problem more generally by defining a *recursive characterization* for computing the value $\ell_{i,j}$, which represents the length of the *longest palindromic substring* in the interval $s_i \dots s_j$. In particular, the length of the interval $s_i \dots s_j$ is given by $len = j - i + 1$.

 - If $i > j \implies len = 0$, then the substring $s_i \dots s_j$ is the *empty substring*, which is *palindromic* by definition. In this case, $\ell_{i,j} = 0$.

 - If $i = j \implies len = 1$, then the substring $s_i \dots s_j$ is made up of a single character, which is *palindromic* by definition. In this case, $\ell_{i,j} = 1$.

 - If $i < j \implies len >= 2$, then the substring $s_i \dots s_j$ is made up of at least two characters. I can split this case into two subcases:

    - If $s_i = s_j$ **and** the *internal substring* $s_{i+1} \dots s_{j-1}$ is a *palindromic substring*, then I can safely say that the substring $s_i \dots s_j$ is also a *palindromic substring*. Because $\ell_{i+1,j-1}$ tracks the max palindrome length within the inner window, it will equal the inner window's full length ($j - i - 1$) **if and only if** the entire inner window is a palindrome. In this case, $\ell_{i,j} = 2 + \ell_{i+1,j-1}$.

    - Otherwise, if $s_i \ne s_j$ or the inner substring is **not** fully palindromic, then the entire interval $s_i \dots s_j$ is not a single palindrome. I must propagate the length of the *longest palindromic substring* found so far from its sub-intervals. In this case, $\ell_{i,j} = \max(\ell_{i+1, j}, \ell_{i,j-1})$.  


I can use these observations to define a recurrence for computing the value of $\ell_{i,j}$:

$$
\ell_{i,j}=
\begin{cases}
0 & \text{if } i > j, \\
1 & \text{if } i = j, \\
2 + \ell_{i+1,j-1} & \text{if } i < j \text{ and } s_i = s_j \text{ and } \ell_{i+1,j-1} = j - i - 1, \\
\max\{\ell_{i+1,j},\ell_{i,j-1}\} & \text{otherwise} 
\end{cases}
$$

I decided to implement a *bottom-up* solution in which I consider each interval $s_i \dots s_j$ of increasing length $len = 2 \dots n$. I use a vector `lengths` to store the lengths $\ell_{i,j}$ found as the algorithm progresses, as well as two variables `startInd` and `maxLen` to keep track of the starting index and maximum length of the *longest palindromic substring* found so far. I can then use these two variables to easily *slice* the final string at the end of the algorithm.


### Pseudocode

```cpp
string longestPalindrome(string s) {

    // length of string, and check for early return
    int n = s.length();
    if (n <= 1) {
        return s;
    }

    // allocate vector for storing lengths found
    vector<vector<int>> lengths(n+1, vector<int>(n+1, 0));

    // trackers for starting index and length of longest palindromic substring found
    int startInd = 0;
    int maxLen = 1;

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

            // if characters match and internal substring is fully palindromic
            if ( (s[i-1] == s[j-1]) && (lengths[i+1][j-1] == j - i - 1) ) {
                lengths[i][j] = 2 + lengths[i+1][j-1];

                // update starting index and length of maximum found, if needed 
                if (lengths[i][j] > maxLen) {
                    maxLen = lengths[i][j];
                    startInd = i - 1;
                }   
            }
            
            // otherwise, maximize length based on sub-intervals
            else {
                lengths[i][j] = std::max(lengths[i+1][j], lengths[i][j-1]);
            }
        }
    }

    // slice using index trackers to return solution
    return s.substr(startInd, maxLen);
}
```

#### Complexity

 * Assuming the input string `s` contains $n$ characters. The algorithm uses two nested loops, resulting in roughly $\frac{n^2}{2}$ iterations. Therefore, the total **time complexity** is $\mathcal{O}(n^2)$.

 * The algorithm uses the vector `lengths` of size $(n+1) \times (n+1)$ to store all computed values of $\ell_{i,j}$. Therefore, the total **space complexity** is $\mathcal{O}(n^2)$.

### Terminal Output
Tests from *LongestPalindromicSubstring.cpp* in `main()`:

```text
Example 1
Input string: 'babad'
Expected: 'bab' (length = 3)
Found: 'bab' (length = 3)
-------------------------------------------

Example 2
Input string: 'cbbd'
Expected: 'bb' (length = 2)
Found: 'bb' (length = 2)
-------------------------------------------

Example 3
Input string: 'hyperionnoirepyhxyzabcdeffedcbax'
Expected: 'hyperionnoirepyh' (length = 16)
Found: 'hyperionnoirepyh' (length = 16)
-------------------------------------------

Example 4
Input string: 'abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba'
Expected: 'abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba' (length = 52)
Found: 'abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba' (length = 52)
-------------------------------------------

Example 5
Input string: 'mississippiimississippi'
Expected: 'ississi' (length = 7)
Found: 'ississi' (length = 7)
-------------------------------------------

Example 6
Input string: 'solosolosolostartupadventureracecaroutdoors'
Expected: 'solosolosolos' (length = 13)
Found: 'solosolosolos' (length = 13)
-------------------------------------------
```


