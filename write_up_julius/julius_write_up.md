Write-up Julius
=============================

Organisational (no points)
--------------

### 0a. Name

**Name**: `Luca Artinian`

### 0b. Student ID

**Student ID**: `2052772`

### 0c. Exercise

**Exercise**: `Julius`

### 0d. Permission
Do we have permission to share and discuss (an anonymized version of) your write-up? (Yes/No)

**Permission granted**: `Yes`



Write-up
--------

### 1. Flag

**Flag**: `SPRITZ{Substitution_ciphers_are_not_secure}`


### 2. Vulnerability
Name and describe the underlying vulnerability you identified, and how you identified it.

**Name**: `Weak/Insecure Encryption`

**Description**: The message was encrypted using a ROT-13 cipher and encoded using Base64 and URL encoding. All of these are easily reversible transformations, exposing the original message.  

**How did you identify it?**: The encoded word in the title was "Caesar" suggesting a substitution cipher. After decoding from Base64, the resulting URL Encoding contained non-valid hexadecimal values, suggesting they were shifted. 


### 3. Weakness
Describe the underlying weakness, i.e., why the vulerability exists.

**Description**: After discovering the encryption algorithm used to be ROT-13, reversing the shifted alphabetic characters using fixed shift of 13 positions is not too hard, also given that there are only 26 possible shifts (brute-force is near-instanteneous) 


### 4. Exploit
Name and describe the exploit (and exploit techniques) that you have used. Further, describe how your exploit works, i.e., how it exploits the identified vulnerabilities to obtain the flag? Describe the cause and effect.

**Name**: ROT13 reversal and layered decoding.

**Description**: I implemented a Python script(`julius_script.py`) to reverse the transformations:

 1. Decode the initial ciphertext from Base64 using base64.b64decode().
 2. Apply ROT13 to alphabetic characters using ord(), chr() and modular arithmetic (% 26), preserving non-alphabetic characters.
 3. Decode the resulting percent-encoded text using urllib.parse.unquote() to retrieve the flag.

**How does it work? (Cause/Effect)**: ROT13 reverses the substitution applied to the message, restoring valid URL-encoded sequences. For example, %7O becomes %7B (`{`) and %5S becomes %5F (`_`). URL decoding then reconstructs the original characters, revealing the flag.


### 5. Countermeasures
Name one possible counter measure and briefly describe how it works and how it would affect your exploit.

**Name and briefly describe one Countermeasure**: Use a stronger encryption.

**How would it affect your exploit?**: It would not work anymore, as decrypting it would then require a secret key.


### 6. Comments
Here is room for your comments, e.g., to report what you have tried and worked and what did not work or if you have learned something new. (Optional)

The Base64-decoded ciphertext initially appeared to contain URL encoding, but sequences such as %7O, %5S and %7Q were invalid because O, S and Q are not hexadecimal digits.

Knowing the expected flag format `SPRITZ{text_text_text}`, I hypothesized that %5S represented underscores and that %7O and %7Q represented the opening and closing curly brackets.

Comparing the characters with their expected hexadecimal equivalents revealed a consistent 13-position shift:

 * O → B (%7B, `{`)
 * S → F (%5F, `_`)
 * Q → D (%7D, `}`)

This confirmed my ROT13 hypothesis.

I used Python rather than shell commands, since I am still learning how to combine shell utilities. Implementing ROT13 myself also helped reinforce character conversion and modular arithmetic.

*Note*: Only after finishing the exercise I thought of potentially using `tr` in shell to replace characters in the encrypted message using the same fixed-position logic, but no need to redo the exercise again.  
Will test in other exercises, if it does prove useful.