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
