# Line Editor in C

A command-line line editor implemented in C using a **dynamic array of strings**. It allows users to create, view, modify, save, load, search, and count text directly from the terminal.

## Team Members

* Jeevika Godachi
* Himaja 
* Deekshitha 

## Data Structure Used

The editor uses a **dynamic array of strings (`char **lines`)** to store document lines.

* `malloc()` is used for memory allocation.
* `realloc()` is used to increase the array capacity when required.
* Each document line is stored separately in dynamically allocated memory.

## Features Implemented

### Core Features

* **INSERT** – Insert a new line at a specified position.
* **DELETE** – Delete a line from the document.
* **DISPLAY** – Display all current lines with line numbers.
* **SAVE** – Save the document to a text file.
* **LOAD** – Load a document from a text file.

### Additional Features

* **SEARCH** – Search for a word or text in the document.
* **COUNT** – Count the number of lines and words.
* **HELP** – Display all available commands.
* **EXIT** – Exit the editor and release allocated memory.

## Commands

| Command   | Description                 |
| --------- | --------------------------- |
| `INSERT`  | Insert a new line           |
| `DELETE`  | Delete an existing line     |
| `DISPLAY` | Display the document        |
| `SAVE`    | Save the document to a file |
| `LOAD`    | Load a document from a file |
| `SEARCH`  | Search text in the document |
| `COUNT`   | Count lines and words       |
| `HELP`    | Display available commands  |
| `EXIT`    | Exit the editor             |

## How to Compile

Open the terminal in the project folder and run:

```bash
gcc lineEditor.c -o lineEditor
```

## How to Run

### Windows

```bash
lineEditor.exe
```

### Linux / macOS

```bash
./lineEditor
```

## Example

```text
EDITOR > INSERT

Enter line number to insert (1 to 1): 1
Enter text: Hello World
Line inserted successfully.

EDITOR > DISPLAY

========== DOCUMENT ==========
1. Hello World
==============================
```

## Project Purpose

This project demonstrates the use of C programming, dynamic memory allocation, arrays of strings, file handling, string operations, and command-based interaction to build a simple terminal-based line editor.

