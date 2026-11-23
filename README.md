*This activity has been created as part of the 42 curriculum by urastell.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor **one line at a time**.

```c
char *get_next_line(int fd);
```

Each call returns the next line of the file pointed to by `fd`, including the terminating `\n` (except for the last line if the file does not end with a `\n`). When there is nothing left to read, or if an error occurs, the function returns `NULL`.

It works with any file descriptor: regular files, the standard input, pipes, etc.

The goal of the project is to learn how to:
- use `read()` to read data in chunks of `BUFFER_SIZE` bytes,
- keep data between two function calls with a **static variable**,
- manage dynamic memory (`malloc` / `free`) without leaks.

## Instructions

### Compilation

The buffer size used by `read()` is set at compile time with the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

If `BUFFER_SIZE` is not defined, the header `get_next_line.h` provides a default value.

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Each returned line is allocated with `malloc`: the caller must `free` it.

To read from the standard input, use `fd = 0`.

### Files

| File | Content |
|---|---|
| `get_next_line.c` | `get_next_line()` and the main steps of the algorithm |
| `get_next_line_utils.c` | Helper functions (string join, copy, newline search, memory) |
| `get_next_line.h` | Prototypes, includes and default `BUFFER_SIZE` |

## Algorithm

### The problem

`read()` does not read lines, it reads **bytes**: up to `BUFFER_SIZE` at a time. A single `read()` can therefore return:
- only part of a line (no `\n` yet): we must read again,
- one or several complete lines **plus the beginning of the next one**.

The bytes read after the `\n` belong to the next line. Since `lseek()` is forbidden, we cannot go back in the file: these bytes must be **kept in memory until the next call**.

### The solution: a static "stash"

The function uses a static variable, `keep`. Unlike a normal local variable, it is not destroyed when the function returns: it keeps its value between calls. It contains the data that has already been read but not yet returned.

Each call to `get_next_line(fd)` follows these steps:

1. **Check the input**: if `fd < 0` or `BUFFER_SIZE <= 0`, return `NULL`.
2. **Fill `keep`** (`ft_read_line`): while `keep` does not contain a `\n` and `read()` still returns data, read `BUFFER_SIZE` bytes and append them to `keep`.
   - The condition is checked **before** reading: if `keep` already contains a complete line from a previous call, no `read()` is done at all.
   - If `read()` returns `-1`, everything is freed and the function returns `NULL`.
3. **Extract the line** (`ft_parse_line`):
   - `get_before_newline` copies everything up to and including the first `\n` (or up to the end if there is none): this is the returned line.
   - `get_after_newline` copies what comes after the `\n`: this becomes the new `keep`.
4. **Return the line**, or `NULL` and free `keep` if there is nothing left to read.

### Example

File content: `"ab\ncdefg\nh"`, `BUFFER_SIZE=4`

| Call | `read()` calls | `keep` after | Returned |
|---|---|---|---|
| 1 | `"ab\nc"` | `"c"` | `"ab\n"` |
| 2 | `"defg"`, `"\nh"` | `"h"` | `"cdefg\n"` |
| 3 | end of file (0) | empty | `"h"` |
| 4 | end of file (0) | freed | `NULL` |

### Why this algorithm

- **It reads as little as possible**: it stops reading as soon as a complete line is available, as required by the subject. The whole file is never read at once (except if `BUFFER_SIZE` is larger than the file).
- **It works with any `BUFFER_SIZE`**: whether it is smaller or larger than a line, the stash handles both cases the same way.
- **It works with any file descriptor**: it only uses `read()`, so files, the standard input and pipes behave the same way.
- **It is simple**: one static string, and each step (read, extract, keep the rest) is a separate function that can be tested on its own.

### BUFFER_SIZE and its limits

- **`BUFFER_SIZE=1`**: it works, but each byte needs one `read()` system call, which is slow on large files.
- **Large values (9999, 10000000)**: the buffer is allocated with `malloc` (on the heap), not as a local array, so a huge value does not overflow the stack. However, `keep` can then contain a large part of the file, and the remainder is copied at every call: with a very large buffer and a very large file, the function becomes slower.
- **Only one file descriptor at a time**: there is a single static variable, so alternating calls on different `fd` would mix their data (not required by this version of the subject).
- **Undefined behaviors** (as stated in the subject): reading a binary file, or a file that changed between two calls before the end of file was reached.

## Resources

- `man 2 read`, `man 2 open`, `man 3 malloc`, `man 3 free`
- [Manipuler un fichier à l'aide de son descripteur en C – codequoi](https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/): file descriptors, `open`, `read` and the reading offset
- 42 subject: *Get Next Line*

### Use of AI

Claude (Anthropic) was used as a tutor throughout the project, with a "questions rather than answers" approach:
- explaining concepts: static variables, how `read()` and file descriptors work, why the leftover bytes must be kept between calls,
- suggesting a step-by-step plan (header, testing `read()` alone, helper functions, then the algorithm),
- reviewing the code after each push: compilation errors, `NULL` cases, memory,
- diagnosing a performance problem: the function called `read()` even when `keep` already contained a complete line, so `keep` kept growing and large `BUFFER_SIZE` values became extremely slow. The fix (checking for a `\n` in the `while` condition, before reading) was found through guided questions,
- writing this README, which I then reviewed.