#include "slush.h"

#include <stdio.h>          // printf, getline
#include <stdlib.h>         // free

void slush_loop() {
    char *line;
    char **args;
    int argc;
    int status;

    while(1) {
        stdin_prompt();
        line = read_in(line);
        args = parse_in(line, &argc);
        status = action(args, argc);

        free(line);
        free(args);
    }
}

int main() {
    printf("Welcome to slush, the silly little underdeveloped shell :)\n");
    slush_loop();
    return 0;
}