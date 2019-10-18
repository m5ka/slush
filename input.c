#include "slush.h"

#include <stdio.h>          // printf, getline
#include <stdlib.h>         // malloc, realloc, free, getenv
#include <string.h>         // strtok
#include <unistd.h>         // getcwd

void stdin_prompt() {
    getcwd(cwd, sizeof(cwd));
    printf(" %s%s$%s ", KGRN, cwd, KNRM);
}

char* read_in() {
    int bufsize = INPUT_BUFSIZE, position = 0;
    char *buffer = malloc(bufsize * sizeof(char));
    int c;

    if(!buffer) {
        fprintf(stderr, "slush: could not allocate input buffer");
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();
        if(c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if(position >= bufsize) {
            bufsize += INPUT_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer) {
                fprintf(stderr, "slush: could not reallocate input buffer");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **parse_in(char *line, int *argc) {
    int bufsize = TOK_BUFSIZE, position = 0;
    char **args = malloc(TOK_BUFSIZE * sizeof(char*));
    char *token;

    if(!args) {
        fprintf(stderr, "slush: could not allocate token parse buffer");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while(token != NULL) {
        args[position] = token;
        position++;

        if(position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            args = realloc(args, bufsize * sizeof(char*));
            if(!args) {
                fprintf(stderr, "slush: could not reallocate token parse buffer");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }

    args[position] = NULL;
    *argc = position;

    return args;
}