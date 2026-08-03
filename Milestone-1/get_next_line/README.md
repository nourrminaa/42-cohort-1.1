*This project has been created as part of the 42 curriculum by nmina.*

# Get Next Line

## 1. Description

Get Next Line (GNL) is a function that reads and returns one line at a time from a file descriptor. Call it in a loop, and you'll get your entire file line by line. Simple as that.

The catch? The `read()` system call doesn't care about lines. It reads arbitrary chunks of bytes based on your buffer size. So if you ask for 10 bytes and your file contains `"Hello\nWorld\n"`, you might get `"Hello\nWorl"` which is more than one line, but not a complete second line.

This project taught me how to:
- Work with **Static Variables** to remember data between function calls
- Manage **Dynamic Memory** without leaking it everywhere
- Handle edge cases that include learning the difference between **Stack** and **Heap**

## 2. Algorithm Explanation

### a. The Core Problem

As I have mentioned above: `read()` gives you chunks and sometimes you only want to extract lines.

### b. My Solution: The 'Leftover' String / Array of Strings

1. **Read and Accumulate**: Keep reading chunks into a `leftover` buffer until you find a `\n` character
2. **Extract the Line**: Once `\n` is found, extract everything up to and including it
3. **Save the Rest**: Keep whatever comes after `\n` in the static `leftover` for the next call
4. **Return**: Give back the line & wait for the next call

### c. Why Static Variables?

Normal variables die when the function returns. Static variables survive. That's how `leftover` remembers what it had from the previous call.

BUT! the pointer of the static `char* leftover` survives and malloc'd memory doesn't free itself. That's where memory leaks come from.. and should be handled.

### d. Bonus: Multiple File Descriptors

The mandatory version uses one static pointer to accumulate the line being read. Works great for one file. But what if you're reading from multiple files simultaneously?
```c
// Mandatory: One box for everyone (considering they have a common file)
static char *leftover;

// Bonus: Each fd gets its own box (for each file descriptor -> for each file)
static char *leftover[OPEN_MAX];
```

Now `leftover[3]` stores data for fd 3, `leftover[4]` for fd 4 and so on. The fd number itself becomes the array index. 

But wait, what is exactly *IS* and fd number? 
### e. File Descriptors

Think of them like hotel room numbers:
- Room 0: Keyboard (always booked)
- Room 1: Screen (always booked)
- Room 2: Errors (always booked)
- Room 3+: Available when you `open()` files

The system assigns the next available number upon file opening. You don't choose its number.

## 3. Instructions

### a. Compilation
```bash
# Basic compilation (-D BUFFER_SIZE=42 by default)
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl

# Different buffer sizes
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl
cc -Wall -Wextra -Werror -D BUFFER_SIZE=10000 get_next_line.c get_next_line_utils.c main.c -o gnl
```

The `-D BUFFER_SIZE=n` flag defines how many bytes `read()` fetches at a time. Without it, the default is 42 (defined in header files).

### b. Usage Example
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("your_file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free the memory allocated!
    }
    close(fd);
    return (0);
}
```



### c. Reading from stdin
```c
// fd 0 is always stdin (keyboard input)
line = get_next_line(0);
```

File descriptor 0 is stdin, 1 is stdout, 2 is stderr. These are automatically available: no need to open them.

### d. Testing for Memory Leaks
```bash
# On macOS (what i have tested on my machine)
leaks -atExit -- ./gnl

# On Linux
valgrind --leak-check=full ./gnl
```

### e. Bonus Compilation
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

## 4. Technical Notes

### a. Buffer Size Behavior

| BUFFER_SIZE | Behavior |
|-------------|----------|
| 1 | Works, but slow (reads one byte at a time) |
| 42 | Default, good balance |
| 10000 | Works fine |
| 10000000 | Stack overflow with stack buffer; use heap allocation |

Due to very large buffer sizes cases, I switched from stack allocation (`char buf[BUFFER_SIZE]`) to heap allocation (`malloc`) to prevent stack overflow.

### b. Stack vs Heap

**Stack**: Fast, automatic cleanup BUT limited size (~**8MB**). Good for small, temporary, fixed-size data.

**Heap**: Manual management with `malloc`/`free`, but unlimited size. Good for data that needs to persist or grow dynamically.

In GNL:
- `buf` (read buffer): Stack for temporary memory & fixed size
- `leftover`: Heap to survive between calls
- Returned `line`: Heap to survive after function returns

### c. What's NOT Handled (Undefined Behavior)

- File modified while reading
- Binary files (null bytes break string functions)

As the subject says, these are undefined behavior. My function is designed for text files that stay unmodified.

## 5. Suprise? Makefile for testing
*use this during testing/evals (if you want to) :)*
``` Makefile
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = get_next_line.c get_next_line_utils.c
SRC_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

all: test.txt main.c
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 $(SRC) main.c -o gnl
	./gnl

bonus: test1.txt test2.txt test3.txt main_bonus.c
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 $(SRC_BONUS) main_bonus.c -o gnl_bonus
	./gnl_bonus

test.txt:
	echo "Hello" > test.txt
	echo "Line 2" >> test.txt
	echo "Line 3" >> test.txt

test1.txt:
	echo "F1 Line1" > test1.txt
	echo "F1 Line2" >> test1.txt
	echo "F1 Line3" >> test1.txt

test2.txt:
	echo "F2 AAA" > test2.txt
	echo "F2 BBB" >> test2.txt

test3.txt:
	echo "F3 Hello" > test3.txt
	echo "F3 World" >> test3.txt

main.c:
	echo '#include "get_next_line.h"' > main.c
	echo '#include <fcntl.h>' >> main.c
	echo '#include <stdio.h>' >> main.c
	echo '' >> main.c
	echo 'int main(void)' >> main.c
	echo '{' >> main.c
	echo '	int fd;' >> main.c
	echo '	char *line;' >> main.c
	echo '' >> main.c
	echo '	fd = open("test.txt", O_RDONLY);' >> main.c
	echo '	line = get_next_line(fd);' >> main.c
	echo '	printf("Line 1: %s", line);' >> main.c
	echo '	free(line);' >> main.c
	echo '	line = get_next_line(fd);' >> main.c
	echo '	printf("Line 2: %s", line);' >> main.c
	echo '	free(line);' >> main.c
	echo '	line = get_next_line(fd);' >> main.c
	echo '	printf("Line 3: %s", line);' >> main.c
	echo '	free(line);' >> main.c
	echo '	line = get_next_line(fd);' >> main.c
	echo '	printf("Line 4: %s\\n", line);' >> main.c
	echo '	close(fd);' >> main.c
	echo '	return 0;' >> main.c
	echo '}' >> main.c

main_bonus.c:
	echo '#include "get_next_line_bonus.h"' > main_bonus.c
	echo '#include <fcntl.h>' >> main_bonus.c
	echo '#include <stdio.h>' >> main_bonus.c
	echo '' >> main_bonus.c
	echo 'int main(void)' >> main_bonus.c
	echo '{' >> main_bonus.c
	echo '	int fd1;' >> main_bonus.c
	echo '	int fd2;' >> main_bonus.c
	echo '	int fd3;' >> main_bonus.c
	echo '	char *line;' >> main_bonus.c
	echo '' >> main_bonus.c
	echo '	fd1 = open("test1.txt", O_RDONLY);' >> main_bonus.c
	echo '	fd2 = open("test2.txt", O_RDONLY);' >> main_bonus.c
	echo '	fd3 = open("test3.txt", O_RDONLY);' >> main_bonus.c
	echo '	line = get_next_line(fd1);' >> main_bonus.c
	echo '	printf("[fd1] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	line = get_next_line(fd2);' >> main_bonus.c
	echo '	printf("[fd2] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	line = get_next_line(fd1);' >> main_bonus.c
	echo '	printf("[fd1] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	line = get_next_line(fd3);' >> main_bonus.c
	echo '	printf("[fd3] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	line = get_next_line(fd2);' >> main_bonus.c
	echo '	printf("[fd2] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	line = get_next_line(fd1);' >> main_bonus.c
	echo '	printf("[fd1] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	line = get_next_line(fd3);' >> main_bonus.c
	echo '	printf("[fd3] %s", line);' >> main_bonus.c
	echo '	free(line);' >> main_bonus.c
	echo '	close(fd1);' >> main_bonus.c
	echo '	close(fd2);' >> main_bonus.c
	echo '	close(fd3);' >> main_bonus.c
	echo '	return 0;' >> main_bonus.c
	echo '}' >> main_bonus.c

tester:
	git clone https://github.com/Tripouille/gnlTester.git
	cd gnlTester && make a

leaks-mac: all
	leaks -atExit -- ./gnl

leaks-linux: all
	valgrind --leak-check=full --track-origins=yes ./gnl

fclean: clean
	$(RM) main.c main_bonus.c test.txt test1.txt test2.txt test3.txt
	$(RM) -r gnlTester
	$(RM) gnl gnl_bonus

re: fclean all

.PHONY: all bonus clean fclean re tester leaks-mac leaks-linux
```

## Resources

- [read() man page]()
- [open() man page]()
- [malloc() man page]()
- [Static variables in C](https://www.geeksforgeeks.org/c/static-variables-in-c/)
- [File descriptors explained](https://medium.com/@tharinduimalka915/linux-file-descriptors-ec945fd36893)
- [GitHub Skills: Communicate using Markdown](https://github.com/skills/communicate-using-markdown)
- [Stack vs Heap Memory](https://www.geeksforgeeks.org/dsa/stack-vs-heap-memory-allocation/)

### Testing
- [gnlTester by Tripouille](https://github.com/Tripouille/gnlTester)

### AI Usage

I used Claude (AI assistant) for:
- **Understanding concepts**: Explaining how `read()` works, why static variables are needed, stack vs heap differences
- **Documentation**: Helping structure this README

The actual code logic and implementation decisions were mine. AI helped me understand *why* things work, not just copy solutions. Every line of code I can explain in defense.

## Author

**nmina** - 42 Beirut

---

*"Reading a line from a file descriptor is way too tedious."*  Not anymore? :p