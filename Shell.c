#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
<<<<<<< HEAD
#include <sys/types.h>
=======

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELM " \t\r\n\a"
>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args) {
    int i;
    printf("Chen Xue's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in: \n");

    for (int i = 0; i < lsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for informaion on other programs.\n");
    return 1;
}

int lsh_exit(char **args) {
    return 0;
}

<<<<<<< HEAD
int lsh_launch(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("lsh");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int lsh_execute(char **args) {
    int i;
    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

char *lsh_read_line(void) {
    #ifdef LSH_USE_STD_GETLINE
=======
char *lsh_read_line(void) {
    //new way
>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8
    char *line = NULL;
    ssize_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
<<<<<<< HEAD
            perror("lsh: getline\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
    #else
    #define LSH_RL_BUFSIZE 1024
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF) {
        exit(EXIT_SUCCESS);
        } else if (c == '\n') {
        buffer[position] = '\0';
        return buffer;
        } else {
        buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    #endif

}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line) {
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;
=======
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;

    // int bufsize = LSH_RL_BUFSIZE;
    // int position = 0;
    // char *buffer = malloc(sizeof(char) * bufsize);
    // int c;

    // if (!buffer) {
    //     fprintf(stderr, "lsh: allocation erroe\n");
    //     exit(EXIT_FAILURE);
    // }

    // while (1) {
    //     c = getchar();

    //     if (c == EOF || c == '\n') {
    //         buffer[position] = '\0';
    //         return buffer;
    //     } else {
    //         buffer[position] = c;
    //     }
    //     position++;

    //     if (position >= bufsize) {
    //         bufsize += LSH_RL_BUFSIZE;
    //         buffer = realloc(buffer, bufsize);
    //         if (!buffer) {
    //             fprintf(stderr, "lsh: allocation error\n");
    //             exit(EXIT_FAILURE);
    //         }
    //     }
    // }
}

char **lsh_split_line(char *line) {
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
<<<<<<< HEAD
    token = strtok(line, LSH_TOK_DELIM);
=======
    token = strtok(line, LSH_TOK_DELM);
>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
<<<<<<< HEAD
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if (!tokens) {
                free(tokens_backup);
=======
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if (!tokens) {
>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
<<<<<<< HEAD
        token = strtok(NULL, LSH_TOK_DELIM);
=======
        token = strtok(NULL, LSH_TOK_DELM);
>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8
    }
    tokens[position] = NULL;
    return tokens;
}

<<<<<<< HEAD
=======
int lsh_launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("lsh");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int lsh_execute(char **args) {
    int i;
    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

>>>>>>> 5b182c59137abe3950611358f31784f5f3beffb8
void lsh_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv){
    lsh_loop();
    return EXIT_SUCCESS;
}