#include "types.h"
#include "user.h"

void head(char *filename,int lines)
{
    int file = open(filename,0);
    char buffer[512];

    if (file < 0)
    {
        printf(2,"Error: Unable to open file %s\n",filename);
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
        printf(1,"Head command is getting executed in kernel mode\n");
        head1(buffer, lines);
        close(file);
    }
}

int main(int argc, char *argv[])
{

    int lines = 14, k = 1;
    char *textFile;
    if (argc > 2 && strcmp(argv[1], "-n") == 0)
    {
        k = 3;
        lines = atoi(argv[2]);
    }
    else if (argc < 2)
    {
        printf(2, "Usage: %s [-n numLines] <filename1> [<filename2> ...]\n", argv[0]);
        exit();
    }

    for (int i = k; i < argc; i++)
    {
        textFile = argv[i];
        head(textFile, lines);
    }
    exit();
}