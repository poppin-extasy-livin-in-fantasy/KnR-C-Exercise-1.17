# Line Folding Tool — K&R Exercise 1.22

> A stream-oriented line folding program based on **Exercise 1.22** from *The C Programming Language* by Brian Kernighan and Dennis Ritchie.

Pure C11 implementation with no dynamic memory allocation, no string libraries — just a fixed-size buffer and a finite state machine working directly against `stdin`.

---

## How It Works

The algorithm uses an **FSM with a fixed-size buffer array** to process an infinite text stream in constant memory.

```
[ Input Stream — getchar() ]
           │
           ▼
┌──────────────────────────┐
│  Buffer (FOLD_LIMIT)     │ ◄── track last_blank_pos
└────────────┬─────────────┘
             │
     FOLD_LIMIT reached?
        │
        ├── No  ──► keep reading
        │
        └── Yes ──► whitespace found in buffer?
                        │
                        ├── Yes ──► flush up to last blank → shift tail → reset
                        └── No  ──► hard break at limit → reset
```

### Edge Cases Handled

| Case | Behaviour |
|---|---|
| Normal lines | Pass through unmodified |
| Line exceeds `FOLD_LIMIT` | Break at last whitespace before the limit |
| Word longer than `FOLD_LIMIT` | Hard break forced at boundary — stream never stalls |
| No dynamic allocation | Memory footprint fixed at compile time |
| Immediate output | Chunks are flushed as soon as they're ready, not buffered until `EOF` |

---

## Configuration

Defined as compile-time constants at the top of the source file:

| Constant | Default | Description |
|---|---|---|
| `FOLD_LIMIT` | `20` | Maximum column width — lines are broken at or before this column |
| `MAXLINE` | `1000` | Physical buffer safety cap |

Change `FOLD_LIMIT` before compiling to target any column width.

---

## Building

### Visual Studio 2026 (MSVC / `cl.exe`)

Open the **Native Tools Command Prompt** and run:

```bat
cl /std:c11 /W4 /O2 Exercise-1.22.c /Fe:folder.exe
```

### GCC / Clang

```sh
gcc -Wall -Wextra -std=c11 -O2 Exercise-1.22.c -o folder
```

---

## Running

```sh
# Interactive — type input, press Ctrl+D (or Ctrl+Z on Windows) to end
./folder

# Pipe a file
cat long_text.txt | ./folder
```

---

## Examples (`FOLD_LIMIT = 20`)

### Standard Word Wrapping

Input:
```
The C Programming Language book is great.
```

Output:
```
The C Programming
Language book is
great.
```

Lines are broken at the last available space before column 20 — words are never split unless unavoidable.

---

### Oversized Word — Hard Break

Input:
```
Supercalifragilisticexpialidocious
```

Output:
```
Supercalifragilistic
expialidocious
```

A word longer than `FOLD_LIMIT` cannot be broken at a space, so a hard cut is forced at the column boundary. The stream continues normally after.

---

## Part of

This exercise is part of my [**K&R C Exercises**](https://github.com/poppin-extasy-livin-in-fantasy/KnR-C-Exercises) repository — working through *The C Programming Language* cover to cover.
