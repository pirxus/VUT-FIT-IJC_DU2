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

struct cBuffer{
    char **buffers;
    unsigned itemCount;
};

typedef cBuffer *cBuffer_t;

cBuffer_t initCircleBuffer(unsigned itemCount);
void freeCircleBuffer(cBuffer_t *buffer);

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

        case 4:
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


            n = strtoul(argv[2], &endptr, 10);

            if (strcmp(endptr, "")) {
                fprintf(stderr, "Error: parameter of '-n' is not decimal:'%s'\n", argv[2]);
                return 1;
            }

            /* TODO cannot fall through */
            source = fopen(argv[3], "r");
            if (source == NULL) {
                fprintf(stderr, "Error: could not open file '%s'\n", argv[1]);
                return 1;
            }

        default:
            break;
    }

    if (n == 0 && plus == false)
        return 0;
    
    if (plus == true) {
        char line[LINE_LIMIT] = {0};

        for (unsigned long i = 0; i < n; i++) {
            fgets(line, LINE_LIMIT, source);
        }

        while (fgets(line, LINE_LIMIT, source)) {
            printf("%s", line);
        }

    } else {

        cBuffer_t lineBuffer = initCircleBuffer(n);
        if (lineBuffer == NULL) {
            freeCircleBuffer(lineBuffer);
            fclose(source);
            return 1;
        }


        int startIndex = 0;
        bool checkLineLength = true;
        for (int i = 0; fgets(cycleLines[i % n], LINE_LIMIT, source) != NULL; i++) {
            startIndex = i + 1;

            if (checkLineLength == true && cycleLines[i % n][LINE_LIMIT - 2] != '\0' &&
                cycleLines[i % n][LINE_LIMIT - 2] != '\n') {
                fprintf(stderr, "Warning: some of the lines have exceeded the \
                        length limit of 1024 characters\n");
                checkLineLength = false;
            }
        }

        for (unsigned long i = 0; i < n; i++) {
            printf("%s", cycleLines[(i + startIndex) % n]);
            free(cycleLines[(i + startIndex) % n]);
        }
        free(cycleLines);
    }

    fclose(source);

    return 0;
}



cBuffer_t initCircleBuffer(unsigned itemCount) {

    cBuffer_t new = malloc(sizeof(struct cBuffer));
    if (new == NULL) {
        fprintf(stderr, "Error: could not allocate memory for line storage\n");
        return NULL;
    }

    new->itemCount = 0;

    new->buffers = malloc(sizeof(char*) * n);
    if (new->buffers == NULL) {
        fprintf(stderr, "Error: could not allocate memory for line storage\n");
        return NULL;
    }

    for (int i = 0; i < itemCount; i++) {
        new->buffers[i] = malloc(sizeof(char*) * LINE_LIMIT);
        if (new->buffers == NULL) {
            fprintf(stderr, "Error: could not allocate memory for line storage\n");
            return NULL;
        }
        new->itemCount++;
    }

    return new;
}

void freeCircleBuffer(cBuffer_t buffer) {
    if (buffer != NULL) {

        for (int i = 0; i < buffer->itemCount; i++)
            free(buffer->buffers[i]);

        free(buffer->buffers);
        free(buffer);
    }
}
