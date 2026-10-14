# C Command-Line Text Editor

**Institution:** REVA University  
**Department:** Computer Science and Information Technology  
**Course:** Portfolio Building - 3rd Semester 

## Project Overview
This project is a command-line text editor built entirely in C. It operates on a line-by-line basis without a GUI, allowing users to create, modify, save, and analyze text documents using typed commands. 

The document state is managed in-memory using a highly efficient static 2D array, ensuring stability and preventing memory leaks during rapid terminal operations.

## Team Members
* Shreyas C
* Shashank G Naik
* Terrence Paul S

## Features Implemented
We successfully implemented the following features based on the competition rubric:

**Core Features (All 4 Completed):**
1. **Insert a line:** Shifts text dynamically to add new lines.
2. **Delete a line:** Removes lines and shifts arrays.
3. **Display the document:** Displays the text with corresponding line numbers.
4. **Save / Load:** Writes to and reads from standard `.txt` files.

**Bonus Features (4 Completed):**
1. **Search:** Locates and prints lines containing specific substrings.
2. **Find & Replace:** Global replacement of targeted words.
3. **Line/Word Count (Stats):** Parses the array to calculate document metrics.
4. **Delete File:** Directly removes saved text files from the disk.

## How to Compile and Run

**1. Compilation**
Open your terminal, navigate to the directory containing `Main.c`, and compile the code using `gcc`:
```bash
gcc Main.c -o editor
```

**2. Running**
- Windows: `editor.exe`
- Linux / macOS: `./editor`

Full command list with examples: see [Help.md](Help.md).
