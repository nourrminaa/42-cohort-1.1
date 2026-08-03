# Libft - My very first C library

This repository contains a personal implementation of the Libft project.

## Summary

- Project: Libft
- Contents: a set of `ft_`-prefixed implementations of common libc functions, additional string/memory utilities and bonus linked-list helpers.

## Contents

The files in this repository implement the functions declared in `libft.h`. Below they are grouped by purpose to make the library easier to navigate.

### Part 1 - Character classification

- `ft_isalpha` - alphabetic check
- `ft_isdigit` - digit check
- `ft_isalnum` - alphanumeric check
- `ft_isascii` - ASCII-range check
- `ft_isprint` - printable-char check
- `ft_tolower` / `ft_toupper` - case conversions

### Part 2 - Memory helpers

- `ft_memset`, `ft_bzero` - fill memory
- `ft_memcpy`, `ft_memmove` - copy memory
- `ft_memchr`, `ft_memcmp` - scan/compare memory
- `ft_calloc` - allocate cleared heap memory

### Part 3 - String basics and searching

- `ft_strlen` - length
- `ft_strlcpy`, `ft_strlcat` - safe copy/concatenate
- `ft_strchr`, `ft_strrchr` - find character
- `ft_strncmp` - compare strings
- `ft_strnstr` - substring search
- `ft_strdup` - duplicate string

### Part 4 - Conversion

- `ft_atoi` - ASCII to integer
- `ft_itoa` - integer to ASCII

### Part 5 - String utilities (allocating)

- `ft_substr` - substring (allocates)
- `ft_strjoin` - join two strings (allocates)
- `ft_strtrim` - trim set of chars from ends
- `ft_split` - split by delimiter into `char **` (allocates)
- `ft_strmapi` / `ft_striteri` - map/iterate with index

### Part 6 - Output helpers

- `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

### Bonus - Singly-linked list (t_list)

- `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstlast`
- `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`

## Build & Makefile

This repository includes a Makefile that follows the project rules. Typical operations:

- Build the library:

```sh
make
```

- Build bonus list functions into the library (rule provided):

```sh
make bonus
```

- Remove object files:

```sh
make clean
```

- Remove object files and the `libft.a` archive:

```sh
make fclean
```

- Rebuild from scratch:

```sh
make re
```

## Makefile details

- The provided `Makefile` uses `gcc` with `CFLAGS = -Wall -Wextra -Werror` to match the project requirements.

## Debugging and spotting memory leaks

### 1. Valgrind

- Valgrind is the easiest way to detect leaks, invalid reads/writes, uninitialized memory use and other memory errors.
- Typical command:

```sh
valgrind --leak-check=full ./your_test_binary [args]
```

- Interpretation:
  - "definitely lost": memory your program allocated and never freed - definite leaks.
  - "indirectly lost": memory only reachable from leaked blocks.
  - "still reachable": memory still referenced at exit (often small and not a leak in short-lived programs, but you should double-check).
  - Valgrind prints stack traces for allocations which helps locate the responsible `malloc`.

Tip: Ensure every `malloc`/`calloc`/`strdup` has a matching `free` in the correct place. For containers (like `char **` returned from `ft_split`), free each element and then the array itself.

### 2. Debuggers - gdb

- On Linux, `gdb` is the standard debugger. Typical workflow:

```sh
gcc -g -O0 -Wall -Wextra -Werror -o test_prog *.c
gdb --args ./test_prog arg1 arg2
# inside gdb
# (gdb) break ft_split
# (gdb) run
# (gdb) bt            # backtrace
# (gdb) frame 0       # inspect frame
# (gdb) print var     # examine variables
# (gdb) step / next
```

## Automated testers and project validation

There are community and school-provided testers that check many edge cases and ensure your functions match expected behavior. A well-known option (search GitHub) : Tripouille/libftTester

### Why use testers?

- They exercise many edge cases that are easy to miss (NULL inputs, empty strings, extremely long inputs, overlap in `memcpy`/`memmove`, boundary sizes for `strlcpy/strlcat`, list edge cases, etc.).
- Use them as feedback: if a tester fails a case, create a minimal repro and debug.

## Skills gained

Working through the Libft project develops several practical skills that go beyond simply reimplementing functions. Key lessons you'll take away:

- C fundamentals: strong understanding of pointers, arrays, strings, function pointers, struct usage and memory ownership conventions.
- Memory management: careful use of `malloc`/`free`, avoiding leaks, choosing between `memcpy` and `memmove` and protecting against off-by-one errors and missing NUL terminators.
- Build tooling: writing and maintaining a `Makefile`, understanding compilation flags (`-Wall -Wextra -Werror`) and how to add debug flags for development builds.
- Code style and maintainability: following the Norm of clean code, splitting functionality into small static helpers when appropriate and writing readable, well-commented code.

These skills are directly transferable to many C projects and are especially valuable for later systems programming, embedded work, or any low-level code where resource management and correctness are critical.
