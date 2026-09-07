# Roman Numeral to Integer

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, `2` is written as `II` in Roman numeral, just two ones added together. `12` is written as `XII`, which is simply `X + II`. The number `27` is written as `XXVII`, which is `XX + V + II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. 
Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. 
The same principle applies to the number nine, which is written as `IX`. 
There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9.
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90.
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.

## Solution

In this problem, it is important to notice the order of magnitude of the Roman numerals and the rule regarding addition/subtraction.
That is, if we treat the string containing the Roman numeral from left to right:

 - if a number is greater than or equal to the number that follows it, then we add its value (e.g., $VI = 5 + 1 = 6$).
 - if a number is strictly smaller than the number that follows it, then we subtract its value (e.g., $IV = 5 - 1 = 4$).

To make things easier, we can create a map of roman numeral to integer values, such as `std::unordered_map<char,int> roman;`.

We can use this to then scan the string from left to right, applying the rule from above to update a counter containing the integer value
to be returned.

Assuming `std::unordered_map<char,int> roman` contains our map of $\text{roman numeral} \to \text{integer value}$ we can operate as follows:

#### Pseudocode

```cpp
int romanNumeralToInteger(std::string str)

    int total = 0;
    int n = str.length();

    for (int i=0; i < n; i++) {

        if (i+1 < n && (roman[str[i]] < roman[str[i+1]]))
            total = total - roman[str[i]];
        else
            total = total + roman[str[i]];
    }

    return total;            
```

#### Complexity

The total **time complexity** is linear $\Theta(n)$ since the for loop runs $\Theta(n)$ times and accessing an element 
stored in a `std::unordered_map` costs $\mathcal{O}(1)$. 

The total **space complexity** is constant $\Theta(1)$ since the mapping structure holds a constant number of elements at any given moment (in this case 7). 
