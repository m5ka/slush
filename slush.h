#define INPUT_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

/* input.c */
void stdin_prompt();
char* read_in();
char **parse_in(char *line, int *argc);

/* builtins.c */
int cmd_exit(char **args);
int cmd_help(char **args);
int count_builtins();

extern char *builtin_cmd_name[];
extern int (*builtin_cmd_func[]) (char**);

/* action.c */
int execute_pipe(char **args1, int argc1, char **args2, int argc2);
int prepare_pipe(char **args, int argc, int pipe_index);
int execute_cmd(char **args, int argc);
int action(char **args, int argc);