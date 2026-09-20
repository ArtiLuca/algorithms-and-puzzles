# Advent of Code 2020 - Day 4: Passport Processing

[Day 4: Passport Processing](https://adventofcode.com/2020/day/4)

You arrive at the airport only to realize that you grabbed your North Pole Credentials instead of your passport. While these documents are extremely similar, North Pole Credentials aren't issued by a country and therefore aren't actually valid documentation for travel in most of the world.

It seems like you're not the only one having problems, though; a very long line has formed for the automatic passport scanners, and the delay could upset your travel itinerary.

Due to some questionable network security, you realize you might be able to solve both of these problems at the same time.

## Part 1
We are given as input batch files containing passport data. We need to validate the passports by checking whether they have all the required fields. 

The expected fields are as follows:

- **byr**: Birth Year
- **iyr**: Issue Year
- **eyr**: Expiration Year
- **hgt**: Height
- **hcl**: Hair Color
- **ecl**: Eye Color
- **pid**: Passport ID
- **cid**: Country ID

Passport data is validated in batch files (our puzzle input). Each passport is represented as a sequence of *key:value* pairs separated by **spaces** or **newlines**. Passports are separated by **blank lines**.

As an example, we are shown the following 4 passports:

```text
ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in
```

In the above example:  
 - the first passport is **valid** as it contains all required fields.
 - the second passport is **not valid** as it is missing the height field `hgt`.
 - the third passport is missing the `cid` field, but we are told to ignore this field in Part 1, so it is considered **valid**.
 - the fourth passport is missing the `cid` field, which is fine, but it is also missing the birth year field `byr`, so it is considered **not valid**.

We are asked to count the number of valid passports from input, treating the `cid` field as *optional* for Part 1.

### Idea
The first (and probably *largest*) portion of solving Day 4 is correctly parsing the batch files from the input. The batch files contain all the passport data, where each passport is separated by a **blank line**. For each passport, the *key:value* pairs corresponding to its fields are separated by **blank spaces** or by a **newline**. 

I decided to implement a struct `Passport` to store all eight passport fields (`byr`, `iyr`, `eyr`, `hgt`, `hcl`, `ecl`, `pid`, `cid`). Since each field is a *key:value* pair, I also implemented a helper method `setField(string key, string value)` to correctly store the parsed values read from the input. 

```cpp 
// represents a single Passport
struct Passport {

    std::string byr, iyr, eyr, hgt, hcl, ecl, pid, cid;

    void setField(const std::string& key, const std::string& value);
    bool isValidPart1() const;
};
```

When *parsing* the input, we can store all the passports in a `vector<Passport> passports` object. 

 - We read the input file one line at a time. Whenever we encounter a **blank line**, it means we have finished reading a single passport and can push it into our vector.
 - To track this state accurately, I opted for a boolean flag `hasData` to indicate whether the current passport has been correctly parsed or if it is empty. Only if we encounter a **blank line** and `hasData == true` do we insert the passport into our vector and reset `hasData = false` to parse the next one.
 - Since the *key:value* pairs for a single passport can be separated by spaces or newlines, multiple pairs could exist on the same line.
 - Therefore, for each line read from the input, we extract each *key:value* token found, and then *split* the string at the `:` character to extract the `key` and `value` strings to pass to our `setField` helper. Each time we successfully find a field, we set `hasData = true`.
 - Since the input file might not end with a trailing **blank line**, I added a final *sanity check* on `hasData == true` after the loop finishes so we do not miss the very last passport.

After correctly parsing all passports, we can simply count the number of **valid passports** by checking which ones contain all required fields, treating the `cid` field as optional. So a passport is **valid** if none of the required Part 1 fields are missing.

Since the parsing phase is a *substantial* part of this problem, the parsing logic is detailed in the pseudocode below:

### Pseudocode

**Parsing Logic**

Assuming that we saved all passports in `std::vector<Passport> passports` and that a single passport is stores as shown in the struct `Passport` above:

```cpp
// helper for setting parsed "key:value" pairs of passport
void Passport::setField(const std::string& key, const std::string& value) {

    if (key == "byr") byr = value;
    else if (key == "iyr") iyr = value;
    else if (key == "eyr") eyr = value;
    else if (key == "hgt") hgt = value;
    else if (key == "hcl") hcl = value;
    else if (key == "ecl") ecl = value;
    else if (key == "pid") pid = value;
    else if (key == "cid") cid = value;
}

// reads all passports from input
void readPassportData() {

    // assuming `puzzleInput` contains the input file and opens correctly, 
    // and `passports` is our vector containing all passports
    
    std::ifstream file(puzzleInput);

    Passport currentPassport;
    std::string line;
    bool hasData = false;
    
    while (std::getline(file, line)) {

        // if blank line, we finished parsing a passports
        if (line.empty()) {
            if (hasData) {
                passports.push_back(currentPassport);
                currentPassport = Passport();
                hasData = false;
            }
            continue;
        }

        // process passport data
        std::istringstream ss(line);
        std::string token;

        while (ss >> token) {
            // find ':' that separates key:value pairs
            size_t pos = token.find(':');
            if (pos != std::string::npos) {
                std::string key = token.substr(0, pos);
                std::string value = token.substr(pos+1);
                currentPassport.setField(key,value);
                hasData = true;
            }
        }
    }

    // check if we skipped very last passport
    if (hasData) {
        passports.push_back(currentPassport);
    }
}
```

**Part 1 Solution**

Once we have successfully parsed all passports from input, we need to count how many are **valid**. Since Part 1 states that the only *optional* field is `cid` we can simply count all passports that have all the other 7 fields as non-empty. 

```cpp
// helper to check if valid passport
bool Passport::isValidPart1() const {

    // if any of the seven required other than 'cid' are missing, not valid
    if (byr.empty() || iyr.empty() || eyr.empty() || hgt.empty() || 
        hcl.empty() || ecl.empty() || pid.empty()) {
            return false;
    }
    else {
        return true;
    }
}

int solvePart1() const {

    // guard
    if (passports.empty()) {
        return 0;
    }

    int valid = 0;
    for (int i = 0; i < (int)passports.size(); i++) {
        if (passports[i].isValid()) {
            valid++;
        }
    }

    return valid;
}
```

#### Complexity
Assuming there are $n$ passports and that each passport contains on average $m$ characters for its data lines. Splitting and tokenizing each passport line is linear in cost relative to the line's length, and the validation for a single passport after parsing remains constant $\mathcal{O}(1)$ in cost. Therefore, the total **time complexity** for Part 1 is $\mathcal{O}(n \times m)$.

Since we store a vector containing all $n$ passports read from input, the total **space complexity** is $\mathcal{O}(n)$.

---

## Part 2
In Part 2, we are told to continue ignoring the `cid` field, but are given rules regarding the values of each other field.

Now, a **valid passport** must meet the following conditions:

 - The *birth year* (`byr`) must be **four digits** and have $1920 \le \text{value} \le 2002$.
 - The *issue year* (`iyr`) must be **four digits** and have $2010 \le \text{value} \le 2020$.
 - The *expiration year* (`eyr`) must be **four digits** and have $2020 \le \text{value} \le 2030$.
 - The *height* (`hgt`) field must be a number followed by either **cm** or **in**.
   - For **cm**, it must be $150 \le \text{number} \le 193$.
   - For **in**, it must be $59 \le \text{number} \le 76$.
 - The *hair color* (`hcl`) must be a **#** followed by **exactly** six characters $[0 \dots 9]$ or $[a \dots f]$.
 - The *eye color* (`ecl`) must be **exactly one** $\in \{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"\}$.
 - The *passport ID* (`pid`) should be a nine-digit number, including leading zeroes.
 - The *country ID* (`cid`) is still ignored, whether missing or not.

### Idea
All these rules now make the validation a bit more complex, and *heavy*. To simplify the validation procedure, I decided to implement new boolean helpers in the `Passport` struct. 

In particular:

 - The helper `isAllDigits(string str)` returns true if `str` is made up entirely of digits ($0 \dots 9$), which can be checked using `std::isdigit`. This helps later conversions using `std::stoi` avoid potential crashes.
 - The helper `isValidYear(string str, int min, int max)` validates that the year field passes the validation done by `isAllDigits`, that it has a length of exactly 4, and that the converted numerical value falls within the given constraints for the specific year field. 
 - The helper `isValidHeight` extracts the last two characters of the `hgt` field to determine whether they are $\text{ cm }$ or $\text{ in }$, splits the string in order to check if all the characters preceding these last two pass `isAllDigits` and then checks the respective height bounds ($150 \dots 193$ for cm, $59 \dots 76$ for in).
 - The helper `isValidHairColor` checks that the `hcl` field has a total length of exactly 7, starts with the character `#` and that the remaining 6 characters are all valid alphanumeric hex values ($0 \dots 9$ or $a \dots f$), which can be done using `std::isxdigit`.   
 - The helper `isValidPassportID` checks that the `pid` field has a length of exactly 9 and that it is passes `isAllDigits`.
 - The helper `isValidEyeColor` checks that the field `ecl` matches exactly one of the values given by the new rules

### Pseudocode
First, the new validation helpers for the struct `Passport` used in Part 2. To prevent undefined behavior or potential crashes, I chose to use `static_cast<unsigned char>` when performing checks that use `isdigit` or `isxdigit`. 

**Note**: In the actual implementation, I used global constants defined in the header file instead of hard-coded values like below.

```cpp
// checks if a string is made up entirely of digits (0-9)
bool Passport::isAllDigits(const std::string& str) const {

    // base check
    if (str.empty()) {
        return false;
    }

    // check that all characters are digits
    for (int i = 0; i < (int)str.length(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    return true;
}

// validates year fields 
bool Passport::isValidYear(const std::string& str, int min, int max) const {

    // check that length is exactly 4 and that they are all digits
    if (str.length() != 4 || !isAllDigits(str)) {
        return false;
    }

    // convert to number and validate against given constraints
    int year = std::stoi(str);
    return ((year >= min) && (year <= max));
}

// validates height field 
bool Passport::isValidHeight() const {

    // base check
    if (hgt.length() < 3) {
        return false;
    }

    // split the string into "number" + "unit"
    std::string unit = hgt.substr(hgt.length() - 2);
    std::string height = hgt.substr(0, hgt.length() - 2);

    // check that all leading characters are digits 
    if (!isAllDigits(height)) {
        return false;
    }

    // convert height and validate against specific unit constraints
    int value = std::stoi(height);
    if (unit == "cm") {
        return ((value >= 150) && (value <= 193));
    }
    else if (unit == "in") {
        return ((value >= 59) && (value <= 76));
    }

    // otherwise, unit suffix is invalid
    return false;
}

// validates hair color field
bool Passport::isValidHairColor() const {

    // must have length of exactly 7 and first character must be '#'
    if (hcl.length() != 7 || hcl[0] != '#') {
        return false;
    }
    
    // all remaining 6 characters must be valid hex characters 0-9, a-f, A-F
    for (int i = 1; i < (int)hcl.length(); i++) {
        if (!std::isxdigit(static_cast<unsigned char>(hcl[i]))) {
            return false;
        }
    }
    return true;
}

// validates passport ID
bool Passport::isValidPassportID() const {

    // must be exactly 9 digits
    if (pid.length() != 9 || !isAllDigits(pid)) {
        return false;
    }
    return true;
}

// validates eye color
bool Passport::isValidEyeColor() const {

    // must match with exactly one of given values
    if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && 
        ecl != "grn" && ecl != "hzl" && ecl != "oth") {
        return false;
    }
    return true;
}
```

The new validation helper `isValidPart2` performs validation by first checking `isValidPart1` and then checking against all the new rules introduced in Part 2 using the helpers above. The logic for `solvePart2` remains the same as `solvePart1`, as we now count the total **valid passports**, only using a different validation process.

```cpp
bool Passport::isValidPart2() const {

    // check Part 1 validation
    if (!isValidPart1()) {
        return false;
    }

    // validate year fields
    if (!isValidYear(byr, 1920, 2002)) {
        return false;
    }
    if (!isValidYear(iyr, 2010, 2020)) {
        return false;
    }
    if (!isValidYear(eyr, 2020, 2030)) {
        return false;
    }

    // validate height and passport ID
    if (!isValidHeight() || !isValidPassportID()) {
        return false;
    }

    // validate hair color and eye color
    if (!isValidHairColor() || !isValidEyeColor()) {
        return false;
    }

    // if no violations were found, passport is valid
    return true;
}

int solvePart2() const {

    // guard
    if (passports.empty()) {
        return 0;
    }

    int valid = 0;
    for (int i = 0; i < (int)passports.size(); i++) {
        if (passports[i].isValidPart2()) {
            valid++;
        }
    }

    return valid;
}
```

#### Complexity
Assuming there are $n$ passports and that each passport contains, on average, $m$ characters for its data lines. The total **time complexity** remains the same as in Part 1: $\mathcal{O}(n \times m)$.

The total **space complexity** also remains unchanged: $\mathcal{O}(n \times m)$.

### Build
Tested using:

```text
g++ -std=c++17 main.cpp PassportProcessing.cpp -o main.exe
./main.exe
```
