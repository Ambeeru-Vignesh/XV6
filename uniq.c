#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    FILE *file = fopen("demo.txt", "r");

    char curr_line[256];
    char prev_line[256] = "";
    bool first_line = true;

    while (fgets(curr_line, sizeof(curr_line), file) != NULL)
    {
        if (strcmp(curr_line, prev_line) != 0)
        {
            if (first_line)
            {
                first_line = false;
                printf("Uniq command is geing executed in user mode.\n");
            }
            printf("%s", curr_line);
            strcpy(prev_line, curr_line);
        }
    }

    fclose(file);
    return 0;
}
