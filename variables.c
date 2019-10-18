#include "slush.h"

#include <stdio.h>      // printf
#include <stdlib.h>     // getenv

void resolve_vars(char **args, int argc) {
    for(int n = 0; n < argc; n++) {
        if(args[n][0] == '$') {
            char* env = getenv((args[n]+1));
            args[n] = env;
        }
    }
}