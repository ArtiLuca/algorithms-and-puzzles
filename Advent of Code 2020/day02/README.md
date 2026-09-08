# Advent of Code 2020 - Day 2: Password Philosophy

## Part 1
In Part 1, we are given a database of passwords and told that the database is corrupted. 
Some passwords dont meet the corporate policy for when the passwords were set.
We want to count the total number of valid passwords according to their corporate policy.

Each line of the database contains a policy in the format `i-j c: str` where `i` and `j` specify the rules of the policy,  
the character `c` is the character associated with that policy, and `str` is the actual password in the corrupted database.  

The policy `i-j c` states that the password `str` relative to that policy is valid only if the character `c` appears   
in the password `str` at least `i` times and at the most `j` times. 

If we indicate with $\text{count(c)}$ the number of times the character `c` appears in `str`,  
the password `str` is considered valid for its given policy if the following is true:

$$
i \le \text{count(c)} \le j
$$ 

For example, some examples include:

```text
1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
```

In the above example:
 - `abcde` is a valid passord since $\text{count('a')} = 2$ and $1 \le \text{count('a')} \le 3$.
 - `cdefg` is NOT a valid password since $\text{count('b')} = 0$ so $1 \le \text{count('b')} \le 3$ is not true.
 - `ccccccccc` is a valid password since $\text{count('c')} = 9$ and $2 \le \text{count('c')} \le 9$.

### Idea
We can scan the database and keep track of each password alongside its corresponding policy.  
We can use a helper struct `Password` to store the information of a single password, and use a vector to hold all the passwords read from input. 

We can then perform validation for each password in linear time by either simply performing a linear search  
and counting the number of occurrences of the password's corresponding policy character.  
Or we can use the inbuilt method `count(str.begin(), std.end(), c)` which also results in linear time.

Since we are dealing with a relatively small list of passwords, we can perform this linear validation across all passwords  
without resulting in drastic time complexities.

We can use the following struct `Password` for keeping track of a single password in the corrupted database:

```cpp
struct Password {
    int low;
    int high;
    char c;
    string psw;
};
```

Assuming we store all passwords in a `vector<Password> P` we can then validate each one using a boolean helper function  
and count the total valid passwords found to get Part 1's solution. 

```cpp
// boolean helper for Password struct
bool isValidPart1() const {

    if (psw.empty()) {
        return false;
    }

    int n = psw.length();
    int count = 0;

    for (int i = 0; i < psw.length(); ++i) {
        if (psw[i] == c) {
            count++;
        }
    }

    if (count >= low && count <= high) { 
        return true;
    }
    else {
        return false;    
    }
}

int countValidPart1(vector<Password> P) const {

    if (P.empty()) {
        return -1;
    }

    int valid = 0;
    for (int i = 0; i < P.size(); ++i) {
        if (P[i].isValidPart1()) {
            valid++;
        }
    }
    return valid;
}
```

#### Complexity
Assuming the database contains $n$ passwords and that each password has at the most $m$ characters.  
The validation of a single password costs $\Theta(m)$ and we do this for all $n$ passwords.  
Therefore, the total **time complexity** for Part 1 is $\Theta(n \times m)$.

The total **space complexity** is $\Theta(n \times m)$ for storing the entire database of passwords read from input.

## Part 2
In Part 2 we are told that the policies regarding valid passwords are actually interpreted differently.  
We are now told that the policy for a password `str` that is `i-j c` actually indicates the *1-index* positions  
in which the character `c` must appear in the password `str`, where exactly one of the positions must contain the  
character `c` in order for the password to be valid.

## Idea
By changing the meaning of the policies some previously non-valid passwords may now actually be valid.  

Keeping into account the positions indicate *1-indexed* positions, we can implement a new boolean validation helper for the struct `Password`.

In particular, the new validation helper must check that **exactly one** position between the two given by the policy  
contains the needed character, so its as if we were evaluating an exclusive OR (XOR) condition. 

That is, for any given password `str` having policy character `c` and policy positions `i` and `j`,  
we must check that the following condition evaluates to true:

$$
(psw[i-1] == c) 
\text{XOR} 
(psw[j-1] == c)
$$

We can then use this new validation helper across all passwords to count the total number of valid passwords  
using the updated corporate password policies.

```cpp
bool isValidPart2() const {

    if (psw.empty()) {
        return false;
    }

    // exclusive OR
    return (psw[i-1] == c) != (psw[j-1] == c);
}

int countValidPart2(vector<Password> P) const {

    if (P.empty()) {
        return -1;
    }

    int valid = 0;
    for (int i = 0; i < (int)P.size(); i++) {
        if (P[i].isValidPart2()) {
            valid++;
        }
    }
    return valid;
}
```

#### Complexity
Assuming the database contains $n$ passwords and that each password has at the most $m$ characters.  
The validation of a single password for Part 2 has a constant cost $\Theta(1)$ since  performing the necessary checks  
remains constant in time and accessing elements of a vector is constant $\Theta(1)$.  

The total **space complexity** remains $\Theta(n \times m)$ as we still have to keep storing the entire database of passwords read from input.

### Build
Tested using

```text
g++ -std=c++17 main.cpp PasswordPhilosophy.cpp -o main.exe  
./main.exe
```
