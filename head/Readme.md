# Implementing `head` on xv6 as a User Program and System Call

## Overview

In this project our main focus is to incorporate the head command into the xv6 operating system as both a user program and a system call. The head command, which complements the tail command is specifically designed to display a number of lines from a given input n. By default it prints the 14 lines of the specified files. If multiple file names are provided each files data is preceded by its file name. When no filename is given head should read from input. It's important to note that if the first argument doesn't begin with " " the default number of lines to be printed should be 14.

To achieve this implementation we need to create a head command, in both user space and kernel mode.

The implementation involves creating a `head` command both in user space and kernel mode.

## Task 1: User Space

In the user space, we will create a `head.c` program that replicates the functionality of the `head` command. This program should display/print the following message: "Head command is getting executed in user mode," followed by the content.

### Code: `head.c`

```c
#include "types.h"
#include "user.h"

void head(char *filename, int lines)
{
    int file = open(filename, 0);

    if (file < 0)
    {
        printf(2, "Error: Unable to open file %s\n", filename);
        return;
    }

    char currentChar;
    char curr_line[256];
    int lineNo = 0;
    int firstIndex = 0;
    int lineCount = 1;

    while (lineCount <= lines && read(file, &currentChar, 1) > 0)
    {

        if (firstIndex == 0)
        {
            printf(1, "Head command is getting executed in user mode.\n");
            firstIndex = 1;
        }

        if (currentChar == '\n')
        {
            curr_line[lineNo] = '\0';
            printf(1, "%s\n", curr_line);
            lineNo = 0;
            lineCount++;
        }
        else
        {
            curr_line[lineNo++] = currentChar;
        }
    }

    close(file);
}

int main(int argc, char *argv[])
{
    int lines = 14;

    if (argc >= 2 && strcmp(argv[1], "-n") == 0)
    {
        if (argc < 4)
        {
            printf(2, "Usage: %s [-n numLines] <filename1> [<filename2> ...]\n", argv[0]);
            exit();
        }

        lines = atoi(argv[2]);
        argv += 3;
        argc -= 3;
    }
    else if (argc < 2)
    {
        printf(2, "Usage: %s [-n numLines] <filename1> [<filename2> ...]\n", argv[0]);
        exit();
    }
    else
    {
        argv++;
        argc--;
    }

    for (int i = 0; i < argc; i++)
    {
        head(argv[i], lines);
    }

    exit();
}
```

## Output Commands

To use the `head` program, you can execute the following commands:

- To display the first 14 lines of `example2.txt`:

```shell
$ head example2.txt
```

![head example2.txt](<images/head example2.txt.png>)

- To specify the number of lines (e.g., 5) to display from `example.txt`:

```shell
$ head -n 5 example2.txt
```

![head -n 5 example2.txt](<images/head -n.png>)

- To display the first 14 lines of `example2.txt` and `example3.txt`:

```shell
$ head example2.txt example3.txt
```

![head example2.txt example3.txt](<images/head multifiles.png>)

- To specify the number of lines (e.g., 5) to display from `example2.txt` and `example3.txt`:

```shell
$ head -n 5 example2.txt example3.txt
```

![head -n 5 example2.txt example3.txt](<images/head -n multifiles.png>)

This project demonstrates the implementation of the `head` command in both user and kernel modes in the xv6 operating system, providing a useful tool for viewing the top N lines of a file or standard input.

# Implementing a System Call for `head` in Kernel Mode

## Introduction

This README provides step-by-step instructions on implementing a system call for the `head` command in kernel mode within the xv6 operating system. The `head` command is typically used to display the first few lines of a text file. By implementing this command as a system call, you can invoke it directly from user-space programs.

## Prerequisites

Before you begin, ensure that you have the following:

- An xv6 development environment set up.
- Familiarity with C programming and system call implementation.
- xv6 source code available and ready for modification.

## Implementation Steps

### Step 1: Modify `user.h`

In the `user.h` header file, add a prototype for the `sys_head1` system call. This step is necessary to declare the system call interface to user-space programs.

```c
int sys_head1(char[], int);
```

### Step 2: Create `sys_head1` Function

In the `sysproc.c` source file, implement the `sys_head1` function. This function will handle the actual `head` logic when called as a system call.

```c
int sys_head1(void) {
    // Implement the head logic here
    return 0;
}
```

### Step 3: Modify `syscall.h`

In the `syscall.h` header file, add a new system call number for `sys_head1`. Assign it a unique number in the `enum` definition.

```c
#define SYS_head1 23  // Replace 23 with a unique number
```

### Step 4: Modify `usys.S`

In the `usys.S` assembly file, add an entry for the `sys_head1` system call. This file defines the user-level system call stubs.

```assembly
SYSCALL(head1)
```

### Step 5: Modify `syscall.c`

In the `syscall.c` source file, add an entry in the `syscalls` array to map the system call number to the `sys_head1` function.

```c
[SYS_head1] sys_head1,
```

### Step 6: Implement the `head` Logic

Inside the `sys_head1` function, implement the logic for the `head` command. This logic should read and process the input text, printing the specified number of lines.

```c
int sys_head1(void) {
    char *s;
    int lines;

    if (argstr(0, &s) < 0 || argint(1, &lines) < 0) {
        cprintf("Error: Invalid arguments\n");
        return -1;
    }

    char s1[512] = {0}, s2[512] = {0};
    int j = 0, lc = 0;

    strncpy(s1, s, sizeof(s1));

    for (int i = 0; i < sizeof(s1); i++) {
        s2[j++] = s1[i];
        if (s1[i] == '\n') {
            cprintf("%s", s2);
            j = 0;
            memset(s2, 0, sizeof(s2));
            lc++;
        }
        if (lc == lines) {
            break;
        }
    }
    return 0;
}
```

### Step 7: Build and Test

Rebuild the xv6 kernel and user-space programs to include the new system call. After the build is successful, you can create user programs that call the `head` system call to display the first few lines of text.

## Usage

To use the `head` system call in user programs, you can invoke it as follows:

```c
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(2, "Usage: %s <numLines> <filename1> [<filename2> ...]\n", argv[0]);
        exit();
    }

    int lines = atoi(argv[1]);

    for (int i = 2; i < argc; i++) {
        printf(1, "head command is getting executed in kernel mode for %s.\n", argv[i]);
        head1(argv[i], lines);
    }

    exit();
}
```

This program reads one or more input files and displays the specified number of lines from the beginning of each file.

---
