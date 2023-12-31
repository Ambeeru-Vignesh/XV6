# Implementing uniq on xv6 as a User Program

## Overview

This project aims to implement a simplified version of the uniq command in the xv6 operating system as a user program. The uniq command is commonly used to remove adjacent duplicate lines from a file. Here are the steps and details of the implementation:

### Steps:

#### 1. Prepare Input File

Create a sample input file named `demo.txt` with the following content:

```shell
I understand the Operating system.
I understand the Operating system.
I understand the Operating system.
I love to work on OS.
I love to work on OS.
Thanks xv6.
```

#### 2. Create `uniq.c` Program

Develop a C program named `uniq.c` that contains the logic for removing adjacent duplicate lines from a file. The code has been written with extensive C libraries to handle file operations and line comparison.

![desirable output](<images/gcc output.png>)

#### 3. Modify `uniq.c` for xv6 Compatibility

Modify `uniq.c` to make it compatible with the xv6 operating system while keeping the logic the same.

![example.txt](images/example.txt.png)
![code part-1](<images/uniq code-1.png>)
![code part-2](<images/uniq code-2.png>)
![code part-3](<images/uniq code-3.png>)
![Makefile](images/Makefile.png)

#### 4. Prepare Environment

In preparation for running the program in the xv6 environment, create a file named `example.txt` with the same content as `demo.txt`. Update the `Makefile` to include both `example.txt` and the modified `uniq.c` to ensure they are included in the xv6 environment.

This is how it should look like after using the `ls` command in xv6 environment.

![Files list](<images/Qemu env files.png>)

#### 5. Enter xv6 Environment

Compile and enter the xv6 environment using the following commands:

```shell
make
make qemu
```

#### 6. Execute uniq Program

Execute the uniq program in the xv6 environment using the following command:

```shell
uniq example.txt
```

![The Output](<images/uniq output.png>)

### Results:

Upon running the `uniq` program, the adjacent duplicate lines are removed from the input file, resulting in a clean and unique list of lines. The program also supports additional options, such as:

Similarly, The output for below commands

- uniq -c example.txt - Returns the count of duplicates preceded by each line.
  ![uniq -c example.txt](<images/uniq -c output.png>)

- uniq -i example.txt - Removes adjacent duplicate lines irrespective of case sensitivity.
  ![uniq -i example.txt](<images/uniq -i output.png>)

- uniq -d example.txt - Returns only duplicate lines.
  ![uniq -d example.txt](<images/uniq -d output.png>)

### Conclusion

This project successfully demonstrates the implementation of the `uniq` command as a user program in the xv6 operating system. It provides a useful tool for managing and processing text files within the xv6 environment.

---

# Implementing a System Call for `uniq` in Kernel Mode

## Introduction

This README provides guidance on implementing a system call for the `uniq` command in kernel mode within the xv6 operating system. The `uniq` command is typically used to remove consecutive duplicate lines from text files. By implementing this command as a system call, you can invoke it directly from user-space programs.

## Prerequisites

Before you begin, ensure that you have the following:

- An xv6 development environment set up.
- Familiarity with C programming and system call implementation.
- xv6 source code available and ready for modification.

## Implementation Steps

### 1. Modify `user.h`

In the `user.h` header file, add a prototype for the `sys_uniq1` system call. This step is necessary to declare the system call interface to user-space programs.

```c
int sys_uniq1(char[]);
```

### 2. Create `sys_uniq1` Function

In the `sysproc.c` source file, implement the `sys_uniq1` function. This function will handle the actual `uniq` logic when called as a system call.

```c
int sys_uniq1(void) {
    // Implement the uniq logic here
    return 0;
}
```

### 3. Modify `syscall.h`

In the `syscall.h` header file, add a new system call number for `sys_uniq1`. Assign it a unique number in the `enum` definition.

```c
#define SYS_uniq1 22  // Replace 22 with a unique number
```

### 4. Modify usys.S

In the `usys.S`` assembly file, add an entry for the sys_uniq1 system call. This file defines the user-level system call stubs.

```c
SYSCALL(uniq1)
```

### 5. Modify `syscall.c`

In the `syscall.c` source file, add an entry in the `syscalls` array to map the system call number to the `sys_uniq1` function.

```c
extern int sys_uniq1(void);
[SYS_uniq1] sys_uniq1,
```

### 6. Implement the `uniq` Logic

Inside the `sys_uniq1` function, implement the logic for the `uniq` command. This logic should read and process the input file, removing consecutive duplicate lines and printing the result.

```c
int sys_uniq1(void) {
    char *file;

    if (argstr(0, &file) < 0)
        return -1;

    char file1[256] = {0};
    strncpy(file1, file, sizeof(file1));

    char curr_line[256] = {0};
    char prev_line[256] = {0};
    int lineIndex = 0;
    int isFirstLine = 1;

    for (int i = 0; i < sizeof(file1); i++) {
        if (file1[i] == '\n' || file1[i] == '\0') {
            curr_line[lineIndex] = '\0';
            if (strncmp(curr_line, prev_line, sizeof(prev_line)) != 0) {
                if (!isFirstLine) {
                    cprintf("\n");
                }
                cprintf("%s", curr_line);
                strncpy(prev_line, curr_line, sizeof(prev_line));
            }
            isFirstLine = 0;
            lineIndex = 0;
        } else {
            curr_line[lineIndex++] = file1[i];
        }
    }
    return 0;
}
```

### 7. Build and Test

Rebuild the xv6 kernel and user-space programs to include the new system call. After the build is successful, you can create user programs that call the `uniq` system call to process text files.

## Usage

To use the `uniq` system call in user programs, you can invoke it as follows:

```c
#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(2, "Usage: %s <filename1> [<filename2> ...]\n", argv[0]);
        exit();
    }

    for (int i = 1; i < argc; i++)
    {
        printf(1, "uniq command is getting executed in kernel mode for %s.\n", argv[i]);
        uniq(argv[i]);
    }

    exit();
}
```

This program reads one or more input files and processes them separately using the `uniq` system call. Each input file's content is processed independently.

---
