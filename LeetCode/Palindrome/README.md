# Palindrome Number

[Palindrome Number](https://leetcode.com/problems/palindrome-number/description/).

Given an integer `x`, return *true* if `x` is a palindrome, and *false* otherwise.

**Follow up**: Could you solve it without converting the integer to a string?

### Converting integer to string

If we convert `x` into a string `str` we can then simply loop half of the length of the string and check if the characters at both ends are a match. This works for integers that are made up of both an even and odd number of digits. In particular, for an odd number of digits, the comparison is simply done between the single character, which is always `true`. 
If we find two non-matching characters, we immediately return `false`. 
Otherwise, if all characters matched we return `true` to indicate that `x` is a palindrome.

#### Pseudocode

```cpp
bool isPalindrome(int x) {
    
    if (x < 0)
        return false;

    std::string str = std::to_string(x);
    int n = str.length();

    for (int i = 0; i < n/2; i++) {
        if (str[i] != str[n - i - 1]) {
            return false;
        }
    }
    
    // no mismatches found
    return true;
}
```

#### Complexity
If $n$ is the number of digits of `x`, converting an integer to a string takes linear time relative to the digit count. 
We iterate over $\Theta(\lfloor \frac{n}{2} \rfloor)$ so therefore the total **time complexity** is $\Theta(n)$.

Since we allocate memory when converting the integer into a string, the total **space complexity** is also $\Theta(n)$.

---

## Not converting to string

If we want to check if the integer `x` is a palindrome without converting it to a string, we can use the *modulo* operator.
Some observations:

 - an integer `x` cannot be palindrome if it is a negative number.
 - an integer `x` cannot be palindrome if it ends with a *0*, unless the number `x` is *0* itself.
 
For example, $-121$ is *not* a palindrome since $-121 \ne 12(-)1$; $100$ is *not* a palindrome since $100 \ne 001 = 1$. 

We can solve the problem without converting to string by taking the reversed half of `x`.  
That is, we use `reversedHalf = 0` and then keep stripping the right-most digits from `x` using the *modulo* operator:  
$digit = x \mod 10$.

We then take the `reversedHalf` and update it by multiplying its previous value by `10` and adding the last extracted digit.
We then update the original integer `x` by performing an integer division: `x = x / 10`.  
This process continues as long as `x > reversedHalf`.  
Once we have extracted the `reverseHalf` we can perform a final check based on if `x` was made up of an even or an odd number of digits: 
 
 - if `x` has an even number of digits, then `x` is palindrome if `x == reversedHalf` (e.g. `1221` -> `12 == 12`).
 - if `x` has an odd number of digits, then `x` is a palindrome if `x == reversedHalf / 10` (e.g. `12321` -> `12` = `123 / 10 = 12`).

#### Pseudocode

```cpp
bool isPalindrome(int x) {

    if (x < 0)
        return false;
    if (x % 10 == 0 && x != 0)
        return false;
        
    int reversedHalf = 0;
    while (x > reversedHalf) {
        int digit = x % 10;
        reversedHalf = (reversedHalf * 10) + digit;
        x = x / 10;
    }    

    return (x == reversedHalf) || (x == reversedHalf / 10);
}
```

### Complexity

If $n$ is the number of digits of `x` we iterate $\Theta(\lfloor \frac{n}{2} \rfloor)$ times, therefore the total **time complexity** remains linear $\Theta(n)$.

Since all operations are done in-place, the total **space complexity** remains constant $\Theta(1)$.