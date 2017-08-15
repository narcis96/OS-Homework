#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char * Read(FILE * source) {
    char * target = NULL;
    char ch;
    int count = 0;
    while ((ch = fgetc(source)) != EOF) {
        count += 1;
        target = (char * ) realloc(target, (count + 1) * sizeof(char * ));
        target[count - 1] = ch;
    }
    return target;
}

int CountLines(const char * source) {
    int n = strlen(source);
    int i, count = 0;
    for (i = 0; i < n; ++i) {
        if (source[i] == '\n')
            count++;
    }
    return count;
}

int CountWords(const char * source) {
    int n = strlen(source);
    int i, count = 0;
    for (i = 0; i < n - 1; ++i) {
        if ((source[i] != ' ' && source[i] != '\n') && (source[i + 1] == ' ' || source[i + 1] == '\n'))
            count++;
    }
    return count;
}
void main(int argc, char * * argv) {
    char * input = (char * )(malloc(4 * sizeof(char * )));
    strcpy(input, "clw");
    const char * s;
    int ok = 0;
    if (argc > 1) {
        if (strstr(argv[1], "-")) {
            input = (char * ) realloc(input, (strlen(argv[1]) + 1) * sizeof(char * ));
            strcpy(input, argv[1]);
            if (argc > 2) {
                FILE * in = fopen(argv[2], "r");
                if ( in == NULL) {
                    fprintf(stderr, "fopen(*) failed in file %s at line # %d\n", __FILE__, __LINE__);
                    exit(EXIT_FAILURE);
                }
                s = Read( in );
                fclose( in );
                ok = 1;
            }
        } else {
            FILE * in = fopen(argv[1], "r");
            if ( in == NULL) {
                fprintf(stderr, "fopen() failed in file %s at line # %d\n", __FILE__, __LINE__);
                exit(EXIT_FAILURE);
            }
            s = Read( in );
            fclose( in );
            ok = 1;
        }
    } else {
        fprintf(stdout, "Waiting for input:...\n");
    }
    if (ok == 0)
        s = Read(stdin);
    if (strstr(input, "w") != NULL) {
        fprintf(stdout, "%d ", CountWords(s));
    }
    if (strstr(input, "l") != NULL) {
        fprintf(stdout, "%d ", CountLines(s));
    }
    if (strstr(input, "c") != NULL) {
        int bytes = strlen(s);
        fprintf(stdout, "%d ", bytes);
    }
    fprintf(stdout, "\n");
    exit(EXIT_SUCCESS);
}
