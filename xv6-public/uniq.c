#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: %s <filename>\n", argv[0]);
        exit();
    }

    char *filename;
    
    int file; //= open(filename, 0);


    if(argc == 3 && (strcmp(argv[1],"-c")==0 || strcmp(argv[1],"-i")==0 || strcmp(argv[1],"-d")==0))
    {
	    filename = argv[2];
    } else {
	    filename = argv[1];
    }

    file = open(filename, 0);

    if (file < 0) {
        printf(2, "Error: Unable to open file %s\n", filename);
        exit();
    }

    char currentChar;
    char curr_line[256];
    char prev_line[256] = "";
    int lineNo = 0;
    int firstIndex = 0;
    char temp[256];
    int count = 0;

    while (read(file, &currentChar, 1) > 0) {

	if (firstIndex == 0) {
		printf(1, "Uniq command is getting executed in user mode.\n");
		firstIndex = 1;
	}
        if (currentChar == '\n') {
            curr_line[lineNo] = '\0'; 
            if (strcmp(argv[1], "-c") == 0) {
    		if ((strcmp(prev_line, curr_line) == 0) || (strcmp(prev_line, "") == 0)) {
        	count++;
    	    } else {
        	printf(1,"%d %s\n", count, prev_line);
        	count = 1;
    	    }
    	       strcpy(prev_line, curr_line);
	    }  else if (strcmp(argv[1], "-i") == 0) {
    		strcpy(temp, curr_line);
    		for (int i = 0; temp[i] != '\n'; i++) {
        		if (temp[i] >= 'A' && temp[i] <= 'Z') {
            		temp[i] = temp[i] + 32;
       		}
    		}
    		if (strcmp(prev_line, temp) != 0) {
        		printf(1,"%s\n", curr_line);
        		strcpy(prev_line, temp);
    		}
	   } else if (strcmp(argv[1], "-d") == 0) {
    		if (strcmp(prev_line, curr_line) == 0) {
        	count++;
        	if (count == 1) {
            		printf(1,"%s\n", curr_line);
        	}
    		} else {
        		count = 0;
    		}
    		strcpy(prev_line, curr_line);
	   } else if (strcmp(curr_line, prev_line) != 0) {
                printf(1, "%s\n", curr_line);
                strcpy(prev_line, curr_line);
            }

            lineNo = 0;                 
        } else {
            curr_line[lineNo++] = currentChar;
        }
    }

    close(file);
    exit();
}

