/**
 *	@file	tail.c
 *	@author	Simon Sedlacek, FIT
 *	@date	28.3.2019
 *	@note	Reseni: IJC-DU2, priklad 1a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** @brief Implementation limit for source line length */
#define LINE_LIMIT 1024

/** @brief Structure implementing the buffer for storing loaded lines */
typedef struct cBuffer{
    char **buffers;
    unsigned itemCount;
} *cBuffer_t;


/** @brief Initializes the circle buffer */
cBuffer_t initCircleBuffer(unsigned itemCount);

/** @brief Frees the memory allocated for the circle buffer */
void freeCircleBuffer(cBuffer_t buffer);

/** @brief Sets the value of each character in an array to zero */
void clearLine(char *line);

/** @brief Skips to the next line */
void nextLine(FILE *source);

/** @brief Reads at most LINE_LIMIT - 1 character from a file and stores them */
int readLine(char *line, FILE *source);

/** @brief Parses the arguments for the program */
int parseArguments(int argc, char *argv[], FILE **source, unsigned *n, bool *plus);

/** @brief Prints the last n lines from a file */
void tail(FILE *source, unsigned n, cBuffer_t lineBuffer);

/** @brief Prints all the lines starting from line n */
void tailPlus(FILE * source, unsigned n);



int main(int argc, char *argv[]) {

    FILE *source;

    /* In posix tail, adding plus to the number after the '-n' argument makes
     * the program start printing the file content from that particular line number */
    bool plus = false;

    /* Indicates either the number of lines to be printed, or the starting line index */
    unsigned n = 10;

    if (parseArguments(argc, argv, &source, &n, &plus) == 1)
        return 1;

    if (n == 0 && plus == false) {
        fclose(source);
        return 0;
    }

    if (plus == true) {

        tailPlus(source, n);

    } else {

        /* Init the circle buffer for the given number of lines */
        cBuffer_t lineBuffer = initCircleBuffer(n);
        if (lineBuffer == NULL) {
            fprintf(stderr, "Error: could not allocate memory for line storage\n");
            freeCircleBuffer(lineBuffer);
            fclose(source);
            return 1;
        }

        tail(source, n, lineBuffer);

        freeCircleBuffer(lineBuffer);
    }

    fclose(source);
    return 0;
}


/*============================================================*/
/*                    Function definitions                    */

void tail(FILE *source, unsigned n, cBuffer_t lineBuffer) {

    /* Indicates whether there has been a line that exceeded the line length limit */
    bool lineLengthExceededPrinted = false;
    int readStatus;

    /* Indicates the position of the 'oldest' line in the buffer */
    int startIndex = 0;

    for (unsigned long i = 0;
            (readStatus = readLine(lineBuffer->buffers[i % n], source)) != EOF;
            startIndex = ++i){

        if (readStatus == 1 && lineLengthExceededPrinted == false) {
            fprintf (stderr, "Warning: a line exceeded the line length "
                    "limit. Proceeding with potencially shortened lines.\n");
            lineLengthExceededPrinted = true;
        }
    }

    /* Print all the stored lines */
    for (unsigned long i = 0; i < n; i++) {
        printf("%s", lineBuffer->buffers[(i + startIndex) % n]);
    }
}

void tailPlus(FILE * source, unsigned n) {

    /* Indicates whether there has been a line that exceeded the line length limit */
    bool lineLengthExceededPrinted = false;
    int readStatus;
    char line[LINE_LIMIT] = {0};

    /* Start indexing from 1 because +0 and +1 options have to behave
     * the same way */
    for (unsigned long i = 1; i < n; i++)
        nextLine(source);

    while ((readStatus = readLine(line, source)) != EOF) {

        if (readStatus == 1 && lineLengthExceededPrinted == false) {
            fprintf (stderr, "Warning: a line exceeded the line length "
                    "limit. Proceeding with potencially shortened lines.\n");
            lineLengthExceededPrinted = true;
        }
        printf("%s", line);
    }
}

void clearLine(char *line) {
    memset(line, 0, LINE_LIMIT);
}

int readLine(char *line, FILE *source) {
    if (fgets(line, LINE_LIMIT, source) == NULL) {
        return EOF;
    }
    int len = strlen(line);

    if (len == LINE_LIMIT - 1) {
        line[LINE_LIMIT - 2] = '\n';
        nextLine(source);
        return 1;
    }
    return 0;

}

void nextLine(FILE *source) {
    int c;
    while ((c = fgetc(source)) != '\n') {
        if (c == EOF)
            break;
    }
}


cBuffer_t initCircleBuffer(unsigned itemCount) {

    cBuffer_t new = malloc(sizeof(struct cBuffer));
    if (new == NULL) {
        return NULL;
    }

    new->itemCount = 0;
    new->buffers = malloc(sizeof(char*) * itemCount);
    if (new->buffers == NULL) {
        return NULL;
    }

    for (unsigned i = 0; i < itemCount; i++) {
        new->buffers[i] = calloc(LINE_LIMIT, 1);

        if (new->buffers == NULL) {
            return NULL;
        }

        new->itemCount++;
    }

    return new;
}

void freeCircleBuffer(cBuffer_t buffer) {
    if (buffer != NULL) {

        for (unsigned i = 0; i < buffer->itemCount; i++) {
            free(buffer->buffers[i]);
        }

        free(buffer->buffers);
        free(buffer);
    }
}

int parseArguments(int argc, char *argv[], FILE **source, unsigned *n, bool *plus) {
        char *endptr = NULL;

        if (argc == 1) {
            *source = stdin;

        } else if (argc == 2) {

            *source = fopen(argv[1], "r");
            if (*source == NULL) {
                fprintf(stderr, "Error: could not open file '%s'\n", argv[1]);
                return 1;
            }
            
        } else if (argc == 3 || argc == 4) {
            if (strcmp("-n", argv[1])) {
                fprintf(stderr, "Error: unknown program argument '%s'\n", argv[1]);
                return 1;
            }

            if (argv[2][0] == '+')
                *plus = true;
            if (argv[2][0] == '-') {
                fprintf(stderr, "Error: the argument '-n' does "
                        "not accept negative values\n");
                return 1;
            }

            *n = strtoul(argv[2], &endptr, 10);

            if (strcmp(endptr, "")) {
                fprintf(stderr, "Error: parameter of '-n' is not decimal:'%s'\n", argv[2]);
                return 1;
            }

            if (argc == 4) {
                *source = fopen(argv[3], "r");
                if (*source == NULL) {
                    fprintf(stderr, "Error: could not open file '%s'\n", argv[3]);
                    return 1;
                }
            } else {
                *source = stdin;
            }

        } else {
            fprintf(stderr, "Error: Too many program arguments\n");
            return 1;
    }
    return 0;
}
