Write-up CH2 EX2
=============================

Organisational 
--------------

### 0a. Name

**Name**: `Luca Artinian`

### 0b. Student ID

**Student ID**: `2052772`

### 0c. Exercise

**Exercise**: `CH2 E2`

### 0d. Permission
Do we have permission to share and discuss (an anonymized version of) your write-up? (Yes/No)

**Permission granted**: `Yes`


Write-up
--------

### 1. Flag

**Note** This exercise has multiple flags, report all of them.

**Flag**:
`SPRITZ{The_fear_of_long_words_is_called_Hippopotomonstrosesquippedaliophobia}`  
`SPRITZ{Congratulations_this_is_a_flag}`  
`SPRITZ{Scientists_used_magnets_to_levitate_a_frog}`  
`SPRITZ{Where_is_the_flag}`   
`SPRITZ{The_Flag_is_in_plain_sight}`  
`SPRITZ{picture_flag}` 

### 2. Vulnerability
-/-


### 3. Weakness
Did you recognize anything about the flags that helped you find them?

The flags followed the recognizable SPRITZ{...} format used in the previous exercise, which gave me a pattern to search for. See Comments for the full process.

### 4. Exploit
How did you use this knowledge to obtain the flags?

I searched recursively through file contents, filenames and directory paths for the known flag pattern, then inspected suspicious files individually. See Comments for the commands and full process.


### 5. Countermeasures
-/-


### 6. Comments
I first tried extracting the ZIP using Windows, but it took a very long time despite the archive being only about 35 MB. The archive contains a very large number of directories, so extraction involves many filesystem metadata operations rather than simply writing a large amount of data. Creating these directories on Windows/NTFS was considerably slower.

I therefore copied the ZIP into Kali/WSL's Linux filesystem using `cp nested_folders.zip ~`, moved to the home directory with `cd ~`, and ran `unzip nested_folders.zip`. Extraction there was significantly faster.

The flag found in the first exercise was enclosed in `SPRITZ{...}` so maybe some flags could also follow this same format. 
My initial idea was that a flag could possibly be in one of three locations: as a filename, as a file's contents, as the directory/path name.

To get a better idea of the directory content I listed all files within using `find . -type f` and then also checking what type of files where found using `find . -type f -exec file {} \;`.

I then decided to search the file contents recursively for any flags that matched the previous format using `grep -Ri "SPRITZ{" .` and found 3 flags:

**SPRITZ{The_fear_of_long_words_is_called_Hippopotomonstrosesquippedaliophobia}**  
**SPRITZ{Congratulations_this_is_a_flag}**  
**SPRITZ{Scientists_used_magnets_to_levitate_a_frog}**

Recursively search for a match on file paths using `find . -type f | grep -F 'SPRITZ{'` gave me one more flag:

**SPRITZ{Where_is_the_flag}**

A suspicious file was *README.md*, and in fact reading it's contents with 

`cat ./FESG4O/lgeN28/fHSt2WAk/Mz91u/3v95imTFs/oQwE1mIl/SPRITZ/The/Flag/is/in/plain/sight/README.md` gave me the hint: 

```text
"It never is about the destination but about the file system path you traversed and the friends you made along the way. (Seriously, check the folder names)".
```

Since the path contained *SPRITZ/The/Flag/is/in/plain/sight/*, I interpreted the directory names as the fifth flag:

**SPRITZ{The_Flag_is_in_plain_sight}**


The final suspicious file was *SPRITZ{flag}_picture.txt*. The earlier file command identified it as a PNG image despite it being listed as *.txt*, so I copied it as a *.png* file using:

`cp './FESG4O/lgeN28/fHSt2WAk/Mz91u/3v95imTFs/oQwE1mIl/bShCkbr/PTDy7/IwKOgcA/nBgWnIHWH/Et02FfbGx/EDtG5nAX/YOJpy77/LLFearP/SPRITZ{flag}_picture.txt' flag_picture.png`. 

Opening it from WSL terminal with  `explorer.exe "$(wslpath -w flag_picture.png)"` revealed the sixth flag:

**SPRITZ{picture_flag}**
