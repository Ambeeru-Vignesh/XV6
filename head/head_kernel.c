#include "types.h"
#include "user.h"

void head(char *filename, int lines)
{
    int file = open(filename, 0);
    char buffer[1024];

    if (file < 0)
    {
        printf(2, "Error: Unable to open file %s\n", filename);
        return;
    }
    // char *filename = "example.txt";

    int n = read(file, buffer, sizeof(buffer));

    if (n < 0)
    {
        printf(2, "Error: Unable to read file %s\n", filename);
        exit();
    }
    else if (n == 0)
    {
        printf(1, "File %s is empty\n", filename);
    }
    else
    {
        printf(1, "Head command is getting executed in user mode.\n");
        head1(buffer, lines);
    }
    close(file);
    exit();
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