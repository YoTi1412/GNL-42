# Get Next Line Project

## Overview

This project is about creating a function that allows reading a line ending with a newline character '\n' from a file descriptor, without knowing its size beforehand.

## Project Description

`get_next_line` is a function designed to read a file line by line, providing a flexible and memory-efficient solution for reading text files in C. Unlike traditional file reading methods, this implementation reads the file in chunks and handles the extraction of lines dynamically.

## Key Features

- Reads lines of any length
- Works with multiple file descriptors
- Handles partial reads efficiently
- Minimal memory overhead
- Follows the 42 School project guidelines

## How It Works

### Static Buffer: The Memory Keeper

The core of the `get_next_line` function uses a static variable to maintain state between function calls:

```c
char *get_next_line(int fd)
{
    static char *remainder;
    // ... implementation details
}
```

#### Benefits of the Static Buffer:
- Persistent memory between function calls
- Continues reading from the last stopped position
- Manages partial reads effectively

### Function Workflow

1. **First Call**:
   - Allocate memory for the buffer
   - Read from the file descriptor
   - Extract the first line
   - Store remaining data in the buffer

2. **Subsequent Calls**:
   - Check for a complete line in the existing buffer
   - If no complete line, read more from the file
   - Extract and return the next line
   - Update the buffer

3. **Final Call**:
   - Return any remaining data
   - Free the buffer
   - Set buffer to NULL

## Implementation Details

### Main Functions

1. **`get_next_line(int fd)`**
   - Entry point of the line reading process
   - Handles file descriptor validation
   - Manages the overall reading strategy

2. **`extract_line(char *remainder)`**
   - Extracts a single line from the buffer
   - Handles newline character detection
   - Allocates memory for the line

3. **`update_remainder(char **remainder, ...)`**
   - Updates the remainder after line extraction
   - Manages memory for the next read

4. **`append_buffer(char **remainder, ...)`**
   - Appends newly read data to the existing remainder
   - Handles buffer concatenation

### Memory Management

- Uses dynamic memory allocation
- Carefully frees memory to prevent leaks
- Handles edge cases like empty files or partial reads

## Compilation

Compile with:
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

## Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

## Limitations and Considerations

- Not thread-safe by default
- Static buffer remains in memory until program termination
- Requires careful memory management

## Performance Optimization

- Configurable `BUFFER_SIZE` for different reading strategies
- Efficient use of static variables
- Minimizes system calls

**Happy Coding!** 🚀📚
