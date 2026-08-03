*This project has been created as part of the 42 curriculum by nmina.*

# ft_printf

## 1. Description

**ft_printf** is a reimplementation of the C standard library function `printf`.

It prints formatted output to **standard output (stdout)** and returns the **number of characters printed**.

Just like the real `printf`, it:
- Parses a **format string**
- Detects **conversion specifiers**
- Fetches arguments using **variadic functions**
- Converts values into readable output

This project helped me understand:
- **Variadic functions** (`va_list`, `va_start`, `va_arg`, `va_end`)
- **Signed vs unsigned** integer behavior
- **Hexadecimal and pointer** representation
- Why counting printed characters is harder than it looks

## 2. Supported Conversions (Mandatory)

| Specifier | Meaning | Argument Type |
|----------|--------|---------------|
| `%c` | Character | `int` |
| `%s` | String | `char *` |
| `%p` | Pointer address | `void *` |
| `%d` | Signed decimal | `int` |
| `%i` | Signed integer | `int` |
| `%u` | Unsigned decimal | `unsigned int` |
| `%x` | Hexadecimal (lowercase) | `unsigned int` |
| `%X` | Hexadecimal (uppercase) | `unsigned int` |
| `%%` | Literal `%` | none |



## 3. How printf Works

### a. The Core Idea

`printf` does not know how many arguments it will receive.

It relies entirely on the **format string** to decide:
- What type to read next
- How to print it

Example:
```c
ft_printf("Age: %d, Name: %s", 21, "Nour");
```
- `%d` → reads an `int`
- `%s` → reads a `char *`

### b. Variadic Functions

Variadic functions allow a function to accept a variable number of arguments.

Tools from `<stdarg.h>`:

| Tool | Purpose |
|-----|--------|
| `va_list` | Stores arguments |
| `va_start` | Initializes reading |
| `va_arg` | Fetches next argument |
| `va_end` | Cleans up |

Important rules:
- You must know the exact type when calling `va_arg`
- `char` is promoted to `int`
- `va_arg` advances automatically

### c. Main Loop Logic

```c
while (*format)
{
    if (*format == '%')
    {
        format++;
        // detect specifier and print
    }
    else
        write(1, format, 1);
    format++;
}
```

- Normal characters → printed directly  
- `%` → triggers argument parsing  



## 4. Project Structure

```text
ft_printf/
├── libft/
│   └── (full libft)
├── ft_printf.c
├── ft_print_char.c
├── ft_print_str.c
├── ft_print_nbr.c
├── ft_print_unsigned.c
├── ft_print_hex.c
├── ft_print_ptr.c
├── ft_printf.h
├── Makefile
└── libftprintf.a
```



## 5. File Responsibilities

| File | Description |
|-----|------------|
| ft_printf.c | Main loop and dispatcher |
| ft_print_char.c | `%c` and `%%` |
| ft_print_str.c | `%s` |
| ft_print_nbr.c | `%d` `%i` |
| ft_print_unsigned.c | `%u` |
| ft_print_hex.c | `%x` `%X` |
| ft_print_ptr.c | `%p` |
| ft_printf.h | Prototypes |


## 6. Technical Notes

### a. Signed vs Unsigned

```c
printf("%d", -1);  // -1
printf("%u", -1);  // 4294967295
```

Same bits in memory, different interpretation:
- `%d` → signed (two’s complement)
- `%u` → unsigned (raw value)

### b. Hexadecimal

- `%x` → lowercase (`ff`)
- `%X` → uppercase (`FF`)
- Base 16
- Uses `unsigned int`

### c. Pointer Printing (`%p`)

Pointers are:
- Printed in hexadecimal
- Always prefixed with `0x`
- Converted using `unsigned long` (64-bit safe)

```c
printf("%p", &x);
```

### d. NULL Strings

If `%s` receives `NULL`, it prints:
```text
(null)
```



## 7. Compilation & Usage

### a. Compilation

```bash
make
```

This generates:
```text
libftprintf.a
```

### b. Usage Example

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s, number = %d\n", "world", 42);
    return (0);
}
```

Compile & run:
```bash
cc main.c -L. -lftprintf
./a.out
```

## Resources

- `man 3 printf`
- `man 2 write`
- `man stdarg`
- Variadic Functions in C
- Two’s Complement Explained

## Author

**nmina**  
42 Beirut
