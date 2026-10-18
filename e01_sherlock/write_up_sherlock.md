Write-up Template Sherlock
=============================

Organisational 
--------------

### 0a. Name

**Name**: `Luca Artinian`

### 0b. Student ID

**Student ID**: `2052772`

### 0c. Exercise

**Exercise**: `Sherlock`

### 0d. Permission
Do we have permission to share and discuss (an anonymized version of) your write-up? (Yes/No)

**Permission granted**: `Yes`



Write-up
--------

### 1. Flag

**Flag**: `BITSCTF{h1d3_1n_pl41n_5173}`


### 2. Vulnerability
-/-


### 3. Weakness
Did you recognize anything about how to obtain the flag?

**Description**: The text in *challenge.txt* contained unusual uppercase letters within lowercase words. Extracting these letters revealed repeated occurrences of **ZERO** and **ONE**, suggesting that the hidden information was represented in binary.


### 4. Exploit
How did you use this knowledge to obtain the flag?

**Name**: Uppercase-letter extraction and binary decoding

**Description**: I extracted the uppercase letters and combined them into a single string using:

`grep -o '[A-Z]' challenge.txt | tr -d '\n'`

I then replaced **ZERO** with 0 and **ONE** with 1:

`grep -o '[A-Z]' challenge.txt | tr -d '\n' | sed 's/ZERO/0/g; s/ONE/1/g'`

Finally, I used CyberChef to decode the resulting binary stream into ASCII text, revealing the flag.

**How does it work? (Cause/Effect)**: The unusual capitalization conceals a sequence of binary digits written as words. Replacing these words with their numerical equivalents and interpreting successive 8-bit groups as ASCII characters reconstructs the original hidden message.


### 5. Countermeasures
-/-


### 6. Comments

Solved using Linux shell commands and CyberChef