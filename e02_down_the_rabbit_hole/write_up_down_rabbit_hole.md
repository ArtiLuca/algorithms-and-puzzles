Write-up Template Down the rabbit hole
=============================

Organisational 
--------------

### 0a. Name

**Name**: `Luca Artinian`

### 0b. Student ID

**Student ID**: `2052772`

### 0c. Exercise

**Exercise**: `Down the rabbit hole`

### 0d. Permission
Do we have permission to share and discuss (an anonymized version of) your write-up? (Yes/No)

**Permission granted**: `Yes`



Write-up
--------

### 1. Flag

**Flag**: `SPRITZ{TIL:A_group_of_owls_is_called_a_parliament}`


### 2. Vulnerability
-/-


### 3. Weakness
Did you recognize anything about how to obtain the flag?

**Description**: The challenge file contained a very large sequence of space-separated 8-bit binary values. Decoding these values revealed another encoded message, accompanied by a hint for the next layer of encoding. This process repeats multiple layers/encodings.


### 4. Exploit
How did you use this knowledge to obtain the flag?

**Name**: Iterative decoding of multiple encoding layers

**Description**: I implemented a Python script (`rabbit_hole_script.py`) to process the initial binary data and decode the successive layers. The script validates the 8-bit groups, converts them into ASCII characters, and then extracts and decodes each subsequent message based on its encoding format.

The decoding sequence was:

*Binary → Base64 → Hex → Base32 → Base64 → Base64 → Hex → Binary → Base64 → URL encoding → Unicode escape sequences*

After the eleventh stage, the script generated an HTML file containing a QR code. Scanning it led to a *Pastebin* message, which I decoded using Base64 followed by URL decoding in *CyberChef* to recover the flag.

**How does it work? (Cause/Effect)**: Each decoding step reverses one encoding layer and reveals the next encoded message, often with an accompanying hint. 

### 5. Countermeasures
-/-


### 6. Comments

The attached `rabbit_hole_script.py` automates the first eleven decoding stages, records their outputs in `all_layers_log.txt`, and generates the HTML containing the QR code. The final QR/Pastebin and decoding steps were performed manually.