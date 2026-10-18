Write-up Template Ultraencoded
=============================

Organisational 
--------------

### 0a. Name

**Name**: `Luca Artinian`

### 0b. Student ID

**Student ID**: `2052772`

### 0c. Exercise

**Exercise**: `Ultraencoded`

### 0d. Permission
Do we have permission to share and discuss (an anonymized version of) your write-up? (Yes/No)

**Permission granted**: `Yes`



Write-up
--------

### 1. Flag

**Flag**: `ALEXCTF{TH15_1S_5UP3R_5ECR3T_TXT}`


### 2. Vulnerability
-/-


### 3. Weakness
Did you recognize anything about how to obtain the flag?

**Description**: The file `zero_one` consisted of repeated **ZERO** and **ONE** words, suggesting a binary representation. After decoding the binary data, the resulting text ended with **==**, indicating possible *Base64* padding. The challenge description also contained a clue pointing toward *Morse code*.


### 4. Exploit
How did you use this knowledge to obtain the flag?

**Name**: Binary, Base64 and Morse code decoding

**Description**: I wrote a Python script (`ultraencoded_script.py`) to replace **ZERO** and **ONE** with 0 and 1, remove whitespace, and interpret the resulting bitstream as successive 8-bit ASCII characters.

The resulting text appeared to be Base64-encoded, so I decoded it using Python's `base64.b64decode()`, obtaining a sequence of Morse code symbols.

I then used a dictionary mapping Morse sequences to alphanumeric characters to decode the message: *ALEXCTFTH15O1SO5UP3RO5ECR3TOTXT*

Using the expected *ALEXCTF{...}* format and interpreting the repeated *O* characters as separators, I reconstructed the final flag.

**How does it work? (Cause/Effect)**: Each encoding layer represents the same underlying information in a different form. Converting ZERO/ONE into binary digits, decoding the resulting bytes from Base64, and translating Morse symbols into characters reveals the concealed message without requiring a secret key.


### 5. Countermeasures
-/-


### 6. Comments

The script is in `ultraencoded_script.py`. I interpreted the morse code character *O* as a separator for this specific to this challenge and not as a general Morse code convention.