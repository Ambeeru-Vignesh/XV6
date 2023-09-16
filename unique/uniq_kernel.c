#include "types.h"
#include "user.h"

void uniq(char *filename)
{
    int file = open(filename, 0);
    char buffer[1024];

    if (file < 0)
    {
        printf(2, "Error: Unable to open file %s\n", filename);
        return;
    }

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
        printf(1, "uniq command is getting executed in kernel mode.\n");
        uniq1(buffer);
    }
    close(file);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf(2, "Usage: %s [-n numLines] <filename1> [<filename2> ...]\n", argv[0]);
        exit();
    }

    for (int i = 1; i < argc; i++)
    {
        uniq(argv[i]);
    }

    exit();
}