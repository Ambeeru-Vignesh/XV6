#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int lines = 14;

    if (argc >= 2 && strcmp(argv[1], "-n") == 0)
    {
        lines = atoi(argv[2]);
        argv += 2;
        argc -= 2;
    }
    else if (argc != 2)
    {
        printf(2, "Usage: %s [-n numLines] <filename>\n", argv[0]);
        exit();
    }

    char *filename = argv[argc - 1];
    int file = open(filename, 0);

    if (file < 0)
    {
        printf(2, "Error: Unable to open file %s\n", filename);
        exit();
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
            printf(1, "Uniq command is getting executed in user mode.\n");
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
    exit();
}