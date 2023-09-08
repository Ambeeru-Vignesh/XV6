#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(2, "Usage: %s <filename>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], 0);
    if (fd < 0)
    {
        printf(2, "Error: Cannot open file %s\n", argv[1]);
        exit();
    }

    char curr_line[256];
    char prev_line[256] = "";
    int first_line = 1;

    while (1)
    {
        int n = read(fd, curr_line, sizeof(curr_line));
        if (n < 0)
        {
            printf(2, "Error reading file\n");
            close(fd);
            exit();
        }
        if (n == 0)
            break;

        curr_line[n] = '\0';

        if (strcmp(curr_line, prev_line) != 0)
        {
            if (first_line)
            {
                first_line = 0;
                printf(1, "Uniq command is getting executed in user mode.\n");
            }
            printf(1, "%s", curr_line);
            strcpy(prev_line, curr_line);
        }
    }

    close(fd);
    exit();
}
