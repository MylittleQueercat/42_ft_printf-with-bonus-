# 🖨️ ft_printf

![Score](https://img.shields.io/badge/Score-125%2F125-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![42](https://img.shields.io/badge/42-Project-black)

## 📌 Project Goal

**ft_printf** is a partial reimplementation of the C standard library's `printf()` function. The goal is to understand how variadic functions work and how a formatted output system is built from scratch using only `write()`.

```c
int ft_printf(const char *format, ...);
```

The function parses a format string, identifies **conversion specifiers** (e.g. `%d`, `%s`), retrieves the corresponding arguments from the variadic list, formats them, writes the result to stdout, and returns the **total number of characters written** — exactly like the real `printf`.

Bonus adds support for **flags** (`-`, `0`, `#`, `+`, space) combined with **width** and **precision**.

---

## 🧠 Key Concepts

### Variadic Functions (`stdarg.h`)
`printf` accepts a variable number of arguments. In C, this is handled with the `va_list` mechanism:

| Macro | Description |
|---|---|
| `va_list ap` | Declare the argument pointer |
| `va_start(ap, last)` | Initialize it, pointing past the last named parameter |
| `va_arg(ap, type)` | Retrieve the next argument as `type` |
| `va_end(ap)` | Clean up |

```c
int ft_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    // parse format, call va_arg(ap, ...) for each specifier
    va_end(ap);
}
```

### Format String Parsing
Walk the format string character by character:
- Regular character → write it directly, increment count
- `%` → enter specifier parsing mode
- Parse optional flags, width, precision (bonus)
- Read the conversion character (`d`, `s`, `x`, etc.)
- Dispatch to the correct handler, pass `ap`

### Mandatory Conversion Specifiers

| Specifier | Argument type | Output |
|---|---|---|
| `%c` | `int` (char) | Single character |
| `%s` | `char *` | String (null → `"(null)"`) |
| `%p` | `void *` | Pointer in hex (`0x...`) |
| `%d` / `%i` | `int` | Signed decimal integer |
| `%u` | `unsigned int` | Unsigned decimal integer |
| `%x` | `unsigned int` | Hex lowercase |
| `%X` | `unsigned int` | Hex uppercase |
| `%%` | — | Literal `%` |

### Return Value
`ft_printf` must return the **exact number of bytes written** to stdout. Every `write()` call's return value must be tracked and accumulated.

### Bonus — Flags, Width & Precision
The full specifier syntax is:
```
%[flags][width][.precision]specifier
```

| Flag | Effect |
|---|---|
| `-` | Left-align within the field width |
| `0` | Pad with zeros instead of spaces |
| `#` | Prefix `0x`/`0X` for `%x`/`%X`, `0` for `%o` |
| `+` | Always print sign for numeric types |
| ` ` (space) | Print a space instead of `+` for positive numbers |

**Width**: minimum field width — pad with spaces (or `0` with the `0` flag) if the output is shorter.

**Precision**: for strings, max characters printed; for integers, minimum digits (zero-padded).

---

## 🚀 Usage

### Compilation (as a library)
```bash
make        # builds libftprintf.a
make bonus  # builds with flag/width/precision support
```

### Linking
```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o program
```

### Example
```c
#include "ft_printf.h"

int main(void)
{
    int n;

    n = ft_printf("Hello, %s! You are %d years old.\n", "Alice", 30);
    ft_printf("Characters written: %d\n", n);

    // Pointer
    int x = 42;
    ft_printf("Address: %p\n", (void *)&x);

    // Hex
    ft_printf("Hex: %x / %X\n", 255, 255);

    // Bonus: flags + width + precision
    ft_printf("|%-10s|\n", "left");     // left-align in width 10
    ft_printf("|%010d|\n", 42);         // zero-pad
    ft_printf("|%+d|\n", 42);           // force sign
    ft_printf("|%#x|\n", 255);          // 0xff prefix
    ft_printf("|%.5s|\n", "hello!");    // precision on string → "hello"
    ft_printf("|%8.3f|\n", 3.14);       // width + precision (if you implement %f)
}
```

---

## 🏗️ Implementation Logic

### Overall Architecture
```
ft_printf(format, ...)
 ├── va_start
 ├── Walk format string
 │    ├── Regular char → write, count++
 │    └── '%' found
 │         ├── [Bonus] parse flags → width → precision
 │         ├── Read specifier char
 │         └── Dispatch to handler(ap, [flags, width, precision])
 └── va_end → return total count
```

### Dispatcher Pattern
A clean approach uses a function that matches the specifier character to a handler:

```c
int handle_specifier(char spec, va_list ap)
{
    if (spec == 'c') return print_char(va_arg(ap, int));
    if (spec == 's') return print_str(va_arg(ap, char *));
    if (spec == 'p') return print_ptr(va_arg(ap, void *));
    if (spec == 'd' || spec == 'i') return print_int(va_arg(ap, int));
    if (spec == 'u') return print_uint(va_arg(ap, unsigned int));
    if (spec == 'x') return print_hex(va_arg(ap, unsigned int), 0);
    if (spec == 'X') return print_hex(va_arg(ap, unsigned int), 1);
    if (spec == '%') return write(1, "%", 1);
    return 0;
}
```

### Printing Integers & Hex
Convert numbers to strings by extracting digits recursively or iteratively (modulo + division). For hex, use a charset string:
```c
char *base_lower = "0123456789abcdef";
char *base_upper = "0123456789ABCDEF";
```

### Printing Pointers
Cast to `unsigned long`, print as hex with the `0x` prefix:
```c
ft_printf("%p", ptr)  →  "0x" + hex(unsigned long)ptr
```
A `NULL` pointer prints `(nil)` to match bash behavior.

### Bonus — Applying Width & Precision
1. Format the raw value (number or string) into a temporary buffer
2. Apply **precision**: truncate string or zero-pad integer
3. Apply **width**: pad with spaces (or `0` if flag set), on the left (default) or right (`-` flag)
4. Apply **`+` / space** sign prefix
5. Apply **`#`** prefix
6. Write the final result and return its length

---

## ⚠️ Common Mistakes & Tricky Points

- **Return value accuracy**: every `write()` must contribute to the count. Don't write directly without adding to the total — even the `%%` case writes 1 character.
- **`%s` with NULL**: `printf(NULL)` as the format is UB, but `printf("%s", NULL)` must print `(null)`. Add a NULL guard in your string handler.
- **`%p` with NULL**: prints `(nil)`, not `0x0` — check real bash to confirm the expected string for your evaluator.
- **`%c` with `\0`**: `ft_printf("%c", 0)` must write one null byte and count it as 1 character written. Don't use string functions that stop at `\0`.
- **Unsigned vs signed**: `%u`, `%x`, `%X` take `unsigned int` — use `va_arg(ap, unsigned int)`, not `int`, to avoid sign-extension bugs on large values.
- **Bonus flag conflicts**: `-` overrides `0` (can't zero-pad a left-aligned field). `+` overrides ` ` (space). Handle precedence explicitly.
- **Precision 0 on integer 0**: `printf("%.0d", 0)` prints nothing — the integer zero with precision zero produces an empty string. A subtle but tested edge case.

---

## ✅ Evaluation Checklist

- [ ] All 8 mandatory specifiers work correctly
- [ ] Return value matches real `printf` in all cases
- [ ] `%s` with NULL prints `(null)`
- [ ] `%p` prints `0x...` format correctly
- [ ] `%%` prints a single `%` and returns 1
- [ ] `%c` with `\0` writes 1 byte and counts it
- [ ] No memory leaks
- [ ] **Bonus**: `-`, `0`, `#`, `+`, space flags all work
- [ ] **Bonus**: width and precision work independently and combined
- [ ] **Bonus**: flag conflicts handled correctly (`-` beats `0`, `+` beats space)

---

## 🛠️ Useful Debug Commands

```bash
# Compare output and return value against real printf
cat main_test.c | grep ft_printf | sed 's/ft_//g' > real_test.c
cc real_test.c -o real && cc main_test.c libftprintf.a -o mine
./real > real.out && ./mine > mine.out
diff real.out mine.out

# Memory check
valgrind --leak-check=full ./mine

# Test edge cases directly
printf "%.0d\n" 0        # should print blank line
printf "%c\n" 0          # null byte + newline
printf "%p\n" 0          # (nil) or 0x0 depending on system
```
