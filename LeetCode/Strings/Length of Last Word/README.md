# Length of Last Word

Problem: [LeetCode](https://leetcode.com/problems/length-of-last-word/)

Given a string `s` consisting of words and spaces, return the *length of the* ***last*** *word in the string*.

A **word** is a maximal **substring** consisting of non-space characters only.

Example 1:  
Input: `s = "Hello World"`  
Output: $5$  
Explanation: The last word is "World" with length 5.

Example 2:  
Input: `s = "   fly me   to   the moon  "`  
Output: $4$  
Explanation: The last word is "moon" with length 4.

Example 3:  
Input: `s = "luffy is still joyboy"`  
Output: $6$  
Explanation: The last word is "joyboy" with length 6.

## Solution
We are told that $1 \le \text{s.length} \le 10^{4}$, that  `s` consists only of English letters and spaces `' '`, and that there will be at least one word in `s`.

### Stringstream Approach

My first idea was to use `stringstream` to process the input string `s`, reading one word at a time. This works, since `stringstream` automatically skips *empty spaces* and *breaks*. I can process each word in the input stream, overwriting each one till I reach the end of the stream. Once this happens, I can simply return the length of the last word processed.

```cpp
int lengthOfLastWord(string s) {

    stringstream ss(s);
    string str;

    while (ss >> str) {
        // keep overwriting each word
    }

    return str.length();
}
```

#### Complexity

 * Assuming the input string `s` has $n$ characters. Processing the entire string takes time proportional to its length. Therefore, the total **time complexity** is $\mathcal{O}(n)$.
 
 * Since I use *stringstream*, this means that the entire string `s` is copied into an internal buffer. Therefore, the total **space complexity** is $\mathcal{O}(n)$.

### Index Tracker Approach

This first solution was the most "intuitive", and works as expected. However, in real-world scenarios, it would be sub-optimal in terms of **space complexity**, since having to copy the entire input string `s` can be quite memory-costly when dealing with very large strings.

To implement a solution that still takes *linear time* but uses no extra *auxiliary space*, I thought of simply counting the length of the last word by processing each character from *right-to-left*. 

 - I use an index tracker `ind` that starts from the very last character of the string.
 - I loop backwards, decrementing `ind` as long as I encounter trailing whitespace characters. Once I break out of this loop, it means I found the first non-whitespace character of the last word.
 - I then continue looping backwards by incrementing a variable `lengthLast` and decrementing `ind` until I either reach a whitespace character or I reach the very first character in the string.


```cpp
int lengthOfLastWord(string s) {

    // initial setup
    int ind = s.length() - 1;
    int lengthLast = 0;

    // skip any trailing whitespace characters
    while (ind >= 0 && s[ind] == ' ') {
        ind--;
    }

    // when I find the last character of the last word, I count how many characters are in it
    while (ind >= 0 && s[ind] != ' ') {
        lengthLast++;
        ind--;
    }

    return lengthLast;
}
```

#### Complexity

 * Assuming the string `s` has $n$ characters. The algorithm iterates at most $n$ times. Therefore, the total **time complexity** remains $\mathcal{O}(n)$ (as in the first approach).

 * Since we only rely on integer index trackers, we do not allocate any *auxiliary space*. Therefore, the total **space complexity** is $\mathcal{O}(1)$ when using this approach.

### Terminal Output

Tests from *LengthLastWord.cpp* in `main()`:

```text
Example 0:
String: Hello World
Length of last word
Using stringstream = 5
Using index tracking = 5

Example 1:
String:    fly me   to   the moon  
Length of last word
Using stringstream = 4
Using index tracking = 4

Example 2:
String: luffy is still joyboy
Length of last word
Using stringstream = 6
Using index tracking = 6

Example 3:
String:  I eat  bland pasta for everysinglemeal     
Length of last word
Using stringstream = 15
Using index tracking = 15

Example 4:
String: all allong the watchtower b
Length of last word
Using stringstream = 1
Using index tracking = 1
```
