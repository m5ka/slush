#include "slush.h"

#include <stdio.h>
#include <stdlib.h>

char *builtin_cmd_name[] = {
    "exit",
    "help"
};

int (*builtin_cmd_func[]) (char**) = {
    &cmd_exit,
    &cmd_help
};

int cmd_exit(char **args) {
    exit(EXIT_SUCCESS);
}

int cmd_help(char **args) {
    printf("Extremely Rudimentary Interchange for Commands (slush)\n");
    printf("If you need help, just use your intuition :* <3\n");
    return 0;
}

int count_builtins() {
    return sizeof(builtin_cmd_name) / sizeof(char*);
}