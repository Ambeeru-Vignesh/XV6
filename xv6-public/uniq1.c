#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(2, "Usage: %s <filename>\n", argv[0]);
        exit();
    }

    char *filename = argv[1];
    int file = open(filename, O_RDONLY); 
    if (file < 0) {
        printf(2, "Error: Unable to open file %s\n", filename);
        exit();
    }

    if (uniq(file) < 0) {
        printf(2, "Error: Uniq command failed\n");
        close(file);
        exit();
    }

    close(file);
    exit();
}

