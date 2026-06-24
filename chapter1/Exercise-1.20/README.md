# -KnR-C-Exercise-1.20

Solution to exercise 1.20 from "The C Programming Language" by Kernighan & Ritchie.
Replaces tab characters in the input with the proper number of spaces to the next tab stop.
Written in C (C11), compiled with GCC / MSVC.

## Example

> Note: `\t` represents a tab character, `·` represents a space.

### Case 1: Tab at the beginning of the line (col = 0)
* **Input:** `\tHelloWorld`
* **Output:** `········HelloWorld` *(8 spaces added)*

### Case 2: Tab after a short word (col = 5)
* **Input:** `hello\tworld`
* **Output:** `hello···world` *(3 spaces added to reach the next tab stop at 8)*

### Case 3: Tab exactly on the tab stop boundary (col = 8)
* **Input:** `compiler\tC`
* **Output:** `compiler········C` *(8 spaces added to reach the next tab stop at 16)*

## Memory Safety & Architecture
Unlike basic implementations that are vulnerable to Buffer Overflow, this version uses strict boundaries validation:
* **State Tracking:** Tracks both the buffer index (`i`) and virtual screen column (`col`) independently.
* **Overflow Protection:** Dynamically checks `if (i + spaces >= lim - 1)` before writing to prevent memory corruption.
