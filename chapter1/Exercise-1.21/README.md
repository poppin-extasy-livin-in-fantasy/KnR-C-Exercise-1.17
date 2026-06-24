# -KnR-C-Exercise-1.21

Solution to exercise 1.21 from "The C Programming Language" by Kernighan & Ritchie.
This program (`entab`) replaces strings of spaces with the minimum number of tabs and spaces to achieve the same spacing.

Written in C (C11), compiled with GCC / Clang.

## How It Works
The program uses an **deferred-write architecture** with an internal tracking buffer ("pocket" for spaces). Instead of writing spaces immediately to the array, it accumulates them until a non-space character is met or a virtual tab stop boundary is reached.

* **Standard Tab Width:** Fixed at 8 characters (`#define TAB_WIDTH 8`) according to the UNIX/ASCII standard.
* **Screen vs. Memory Tracking:** Uses `col` to track the virtual screen position and `spaces` to count accumulated spaces.

## Memory Safety & Protection
The implementation strictly prevents **Buffer Overflow** vulnerabilities:
* Prior to writing any character (including deferred spaces and `\n`), the buffer index is validated against the hard limit: `if (i < lim - 1)`.
* Prevents memory corruption even if the input line exceeds `MAXLINE`.

## Example

### Case 1: Compressing spaces at the start of a line
* **Input:** `        Hello` (8 spaces)
* **Output:** `\tHello` (Compressed into 1 tab character)

### Case 2: Mixed tabs and spaces inside text
* **Input:** `abc     de` (5 spaces after a 3-character word)
* **Output:** `abc\tde` (Compressed into 1 tab because 3 + 5 = 8, reaching the tab stop)

### Case 3: Spaces that don't reach the boundary
* **Input:** `hi   world` (3 spaces at `col = 2`)
* **Output:** `hi   world` (Kept as 3 spaces, as converting to `\t` would break visual layout)
