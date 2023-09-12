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
