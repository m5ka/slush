#include "slush.h"

#include <stdio.h>          // printf, getline
#include <stdlib.h>         // malloc, realloc, free
#include <sys/wait.h>       // waitpid
#include <unistd.h>         // pid_t, fork, ssize_t, execvp, pipe, dup2, close
#include <string.h>         // strtok, strcmp

int execute_pipe(char **args1, int argc1, char **args2, int argc2) {
    pid_t pid1, pid2;
    int fd[2];
    int status;
    pipe(fd);

    pid1 = fork();
    if(pid1 == 0) {
        // Child process
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        if(execvp(args1[0], args1) == -1) {
            perror("slush");
        }
        _exit(EXIT_FAILURE);
    } else if(pid1 < 0) {
        // Error
        perror("slush");
        return -1;
    }

    pid2 = fork();
    if(pid2 == 0) {
        // Child process
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        if(execvp(args2[0], args2) == -1) {
            perror("slush");
        }
        _exit(EXIT_FAILURE);
    } else if(pid2 < 0) {
        // Error
        perror("slush");
        return -1;
    }

    // Only parent process will get this far, close pipes
    close(fd[0]);
    close(fd[1]);
    // Wait for children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);

    return status;
}

// pipe_start (int) := index of first command after the pipe
int prepare_pipe(char **args, int argc, int pipe_start) {
    int argc2 = argc - pipe_start;
    int argc1 = argc - (argc2 + 1);

    char **args1 = malloc((argc1+1) * sizeof(char*));
    char **args2 = malloc((argc2+1) * sizeof(char*));

    if(!args1) {
        fprintf(stderr, "slush: could not allocate token buffer for first command");
        exit(EXIT_FAILURE);
    }
    if(!args2) {
        fprintf(stderr, "slush: could not allocate token buffer for second command");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while(i < argc1) {
        args1[i] = args[i];
        i++;
    }
    args1[i] = NULL;

    int j = 0;
    while(j < argc2) {
        args2[j] = args[pipe_start + j];
        j++;
    }
    args2[j] = NULL;

    int status = execute_pipe(args1, argc1, args2, argc2);
    free(args1);
    free(args2);
    return status;
}

int execute_cmd(char **args, int argc) {
    pid_t pid;
    int status;
    
    if(!(pid = fork())) {
        // Child process
        if(execvp(args[0], args) == -1) {
            perror("slush");
        }
        _exit(EXIT_FAILURE);
    } else if(pid < 0) {
        // Error
        perror("slush");
        return -1;
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }

    return status;
}

int action(char **args, int argc) {
    if(args[0] == NULL) {
        return 1;
    }

    for(int n = 0; n < argc; n++) {
        if(strcmp(args[n], "|") == 0) {
            // Make sure there are arguments after the pipe
            if(argc > n+1)
                return prepare_pipe(args, argc, (n+1));
            fprintf(stderr, "slush: expecting a command but instead found end of statement");
            return 1;
        }
    }

    for(int i = 0; i < count_builtins(); i++) {
        if(strcmp(args[0], builtin_cmd_name[i]) == 0) {
            return (*builtin_cmd_func[i])(args, argc);
        }
    }

    return execute_cmd(args, argc);
}