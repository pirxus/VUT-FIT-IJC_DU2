/**
 * @file tail.c
 * @author
 * @date
 * @note
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_LIMIT 1024

int main(int argc, char *argv[]) {

    FILE *source;
    bool plus = false;
    unsigned long n = 10;

    switch (argc) {
        case 1:
            source = stdin;
            break;

        case 2:
            if (!strcmp("-n", argv[1])) {
                fprintf(stderr, "Error: option '-n' requires an argument\n");
                return 1;
            }

            source = fopen(argv[1], "r");
            if (source == NULL) {
                fprintf(stderr, "Error: could not open file '%s'\n", argv[1]);
                return 1;
            }
            break;

        case 4:

            /* TODO cannot fall through */
            source = fopen(argv[3], "r");
            if (source == NULL) {
                fprintf(stderr, "Error: could not open file '%s'\n", argv[1]);
                return 1;
            }
            
        case 3:
            if (strcmp("-n", argv[1])) {
                fprintf(stderr, "Error: unknown program argument '%s'\n", argv[1]);
                return 1;
            }

            if (argv[2][0] == '+')
                plus = true;
            if (argv[2][0] == '-') {
                fprintf(stderr, "Error: the argument '-n' does \
                        not accept negative values\n");
                return 1;
            }


            char *endptr = NULL;
            n = strtoul(argv[2], &endptr, 10);

            if (strcmp(endptr, "")) {
                fprintf(stderr, "Error: parameter of '-n' is not decimal:'%s'\n", argv[2]);
                return 1;
            }

            source = stdin;
            break;

        default:
            break;
    }

    if (n == 0 && plus == false)
        return 0;
    
    if (plus == true) {

    } else {

        char **cycleLines = malloc(sizeof(char *) * n);
        if (cycleLines == NULL) {
            fprintf(stderr, "Error: could not allocate memory for line storage\n");
            fclose(source);
            return 1;
        }

        /* alloc memory for the cycle buffer */
        for (unsigned long i = 0; i < n; i++) {
            cycleLines[i] = calloc(LINE_LIMIT, 1);
            if (cycleLines[i] == NULL) {
                fprintf(stderr, "Error: could not allocate memory for line storage\n");
                fclose(source);
                return 1;
            }
        }

        bool checkLineLength = true;
        for (int i = 0; fgets(cycleLines[i % n], LINE_LIMIT, source) != NULL; i++) {

            if (checkLineLength == true && cycleLines[i % n][LINE_LIMIT - 2] != '\0' &&
                cycleLines[i % n][LINE_LIMIT - 2] != '\n') {
                fprintf(stderr, "Warning: some of the lines have exceeded the \
                        length limit of 1024 characters\n");
            }
        }

        for (unsigned long i = 0; i < n; i++) {
            printf("%s", cycleLines[i % n]);
            free(cycleLines[i % n]);
        }
        free(cycleLines);
    }

    fclose(source);



    return 0;
}
