#include "slush.h"

#include <stdio.h>          // printf, getline
#include <stdlib.h>         // malloc, realloc, free
#include <string.h>         // strtok

void stdin_prompt() {
    printf(" %s$%s ", KGRN, KNRM);
}

char* read_in() {
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
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