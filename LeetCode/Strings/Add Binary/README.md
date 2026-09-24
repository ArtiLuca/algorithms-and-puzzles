# Add Binary

Problem: [LeetCode](https://leetcode.com/problems/add-binary/description/)

Given two binary strings `a` and `b`, return *their sum as a binary string*.

Example 1:  
Input: `a = "11"`, `b = "1"`  
Output: `"100"`

Example 2:  
Input: `a = "1010", b = "1011"`  
Output: `"10101"`

## Solution 
We are told that $1 \le \text{a.length, b.length} \le 10^{4}$, that `a` and `b` consist only of `'0'` or `'1'` characters, and that each string does not contain leading zeros except for the zero itself.

Since the length of both strings can go up to $10^{4}$, I cannot convert the strings into their corresponding numerical values, as this would potentially cause **overflow** when using `int` or even `long long`. 

To avoid this, I implemented a solution using a method I recently learned is called the **schoolbook addition method**. I perform the addition by iterating over both strings from *right-to-left*: from their *least significant* to *most significant* digit. As I do this, I also keep track of any potential *carryover* from the previous operation. 

I used two index trackers `indA` and `indB` to keep track of the current digit in each string being evaluated. These start at the *rightmost digit* of each string, and the `carry` value is initially set to 0. After allocating the string `result`, I loop as long as *either* string has any digits remaining or there is any leftover *carry* to deal with. 

Then, at every iteration:

 - Set the current `sum` to any leftover `carry` from the previous iteration.
   
 - If `a` has any digits remaining, I convert the current digit to its corresponding numerical value using the *ASCII trick* of subtracting `'0'`.
   I update `sum` by adding the value and then decrement `indA` by 1. If `b` has any digits remaining, I apply the same process.
     
 - Update the `carry` value using integer division and then use the *modulo operator* to get the correct digit. This is *appended* to the `result` string before moving to the next iteration. 

When both strings have exhausted their digits, and there is no leftover carry, I must **reverse** the string `result` before returning it, since I *appended* each digit onto the string `result` in **reverse order**. Thankfully, the library *<algorithm>* provides a useful function `reverse`, which does exactly this *in-place*.

### Pseudocode

```cpp
string addBinary(string a, string b) {

    string result = "";    // result string
    int indA = a.length() - 1;  // string a index tracker
    int indB = b.length() - 1;  // string b index tracker
    int carry = 0;              // carry value
    
    // add digits from right-to-left, as long as either string has digits left,
    // or there is any leftover carry
    while (indA >= 0 || indB >= 0 || carry > 0) {

        // account for any leftover carry in current sum
        int sum = carry;

        // update sum with digits from both strings (if there are any)
        if (indA >= 0) {
            sum += a[indA] - '0';
            indA--;
        }
        if (indB >= 0) {
            sum += b[indB] - '0';
            indB--;
        }

        // update carry using integer division
        carry = sum / 2;

        // use modulo to append digit to result string
        result += to_string(sum % 2);
    }
    
    // reverse result string before returning
    reverse(result.begin(), result.end());
    return result;
}
```

#### Complexity

 * Assuming string `a` has $n_{a}$ digits and string `b` has $n_{b}$ digits. Assuming $n = \max{(n_{a},n_{b})}$, the algorithm performs at most $n+1$ iterations (where the $+1$ is for any potential *leftover carry*). Therefore, the total **time complexity** is $\mathcal{O}(n)$.

 * Since we allocate the string `result`, which has length $n = \max{(n_{a},n_{b})}$, the total **space complexity** is $\mathcal{O}(n)$.

#### Terminal Output

```text
Example 1:
'11' + '1' (4)
Expected: '100'
Output: 100

Example 2:
'1010' + '1011'(21)
Expected: '10101'
Output: 10101

Example 3:
'001' + '1001' (10)
Expected: '1010'
Output: 1010

Example 4:
'11001' + '111001' (82)
Expected: '1010010'
Output: 1010010
```
