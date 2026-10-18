Write-up CH2 EX3
=============================

Organisational 
--------------

### 0a. Name

**Name**: `Luca Artinian`

### 0b. Student ID

**Student ID**: `2052772`

### 0c. Exercise

**Exercise**: `CH2 E3`

### 0d. Permission
Do we have permission to share and discuss (an anonymized version of) your write-up? (Yes/No)

**Permission granted**: `Yes`



Write-up
--------

### 1. Flag

**Flag**: `Ceremonial plates`


### 2. Vulnerability
-/-


### 3. Weakness
Did you recognize anything about how to obtain the flag?

**Description**: The triplets $(x,y,z)$ indicated the paragraph number, line number and word number within that line in the given *.txt* file.


### 4. Exploit
How did you use this knowledge to obtain the flag?

Visually finding the corresponding words in a text editor.



### 5. Countermeasures
-/-


### 6. Comments
Here is room for your comments, e.g., to report what you have tried and worked and what did not work or if you have learned something new. (Optional)

I interpreted the triplets $(x,y,z)$ as:

```text
x = paragraph
y = line
z = word
```

This interpretation lead me to:

```text
(1, 9, 4): the
(4, 2, 8): flag
(4, 8, 3): is
(7, 1, 5): Ceremonial
(8,10, 1): plates
```