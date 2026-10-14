# Line Editor - Command Reference Guide

This document outlines all available commands for the C Line Editor. The editor processes one command per line. 

## Core Commands

* **DISPLAY**
  * **Description:** Prints the entire document to the terminal with line numbers.
  * **Usage:** `DISPLAY`
  *   - **Example:** `DISPLAY`

* **INSERT**
  * **Description:** Adds a new line of text at the specified line number, shifting existing lines down.
  * **Usage:** `INSERT <line_number> <text>`
  * **Example:** `INSERT 1 This is my new first line.`

* **DELETE**
  * **Description:** Removes the text at the specified line number, shifting subsequent lines up to fill the gap.
  * **Usage:** `DELETE <line_number>`
  * **Example:** `DELETE 3`

* **SAVE**
  * **Description:** Writes the current in-memory document to a specified text file on your disk.
  * **Usage:** `SAVE <filename.txt>`
  * **Example:** `SAVE my_document.txt`

* **LOAD**
  * **Description:** Clears the current document and loads text line-by-line from a specified file.
  * **Usage:** `LOAD <filename.txt>`
  * **Example:** `LOAD my_document.txt`

## Bonus Commands

* **SEARCH**
  * **Description:** Searches the entire document and prints any lines (with their line numbers) that contain the specified word or phrase.
  * **Usage:** `SEARCH <phrase>`
  * **Example:** `SEARCH Hello World`

* **REPLACE**
  * **Description:** Finds every instance of a specific word across the entire document and replaces it with a new word or phrase.
  * **Usage:** `REPLACE <old_word> <new_word>`
  * **Example:** `REPLACE apple orange`

* **STATS**
  * **Description:** Calculates and displays the total number of lines and the total number of words in the current document.
  * **Usage:** `STATS`
  *   - **Example:** `STATS`

* **DELETE_FILE**
  * **Description:** Permanently deletes an actual text file from your local disk.
  * **Usage:** `DELETE_FILE <filename.txt>`
  * **Example:** `DELETE_FILE old_draft.txt`

## System Commands

* **HELP** - Displays a quick-reference cheat sheet of commands within the editor.
* **EXIT** - Safely closes the editor and returns to the terminal.
