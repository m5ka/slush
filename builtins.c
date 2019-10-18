#include "slush.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *builtin_cmd_name[] = {
    "exit", "cd", "help"
};

int (*builtin_cmd_func[]) (char**, int) = {
    &cmd_exit,
    &cmd_cd,
    &cmd_help
};

int cmd_exit(char **args, int argc) {
    exit(EXIT_SUCCESS);
}

int cmd_cd(char **args, int argc) {
    if(argc > 1) {
        chdir(args[1]);
    } else {
        chdir(getenv("HOME"));
    }
}

int cmd_help(char **args, int argc) {
    printf("Extremely Rudimentary Interchange for Commands (slush)\n");
    printf("If you need help, just use your intuition :* <3\n");
    return 0;
}

int count_builtins() {
    return sizeof(builtin_cmd_name) / sizeof(char*);
}