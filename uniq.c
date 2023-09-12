#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(2, "Usage: %s <filename>\n", argv[0]);
        exit();
    }

    char *filename = argv[1];
    int file = open(filename, 0);

    if (argc == 3 && (strcmp(argv[1] == 'd') || strcmp(argv[1] == 'i') || strcmp(argv[1] == 'd')))
    {
        filename = argv[2];
    }
    else
    {
        filename = argv[1];
    }

    if (file < 0)
    {
        printf(2, "Error: Unable to open file %s\n", filename);
        exit();
    }

    char currentChar;
    char curr_line[256];
    char prev_line[256] = "";
    int lineNo = 0;
    int firstIndex = 0;

    while (read(file, &currentChar, 1) > 0)
    {

        if (firstIndex == 0)
        {
            printf(1, "Uniq command is getting executed in user mode.\n");
            firstIndex = 1;
        }
        if (currentChar == '\n')
        {
            curr_line[lineNo] = '\0';

            if (strcmp(curr_line, prev_line) != 0)
            {
                printf(1, "%s\n", curr_line);
                strcpy(prev_line, curr_line);
            }

            lineNo = 0;
        }
        else
        {
            curr_line[lineNo++] = currentChar;
        }
    }

    close(file);
    exit();
}