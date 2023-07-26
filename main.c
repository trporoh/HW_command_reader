#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* sgets(char* buff, unsigned int size) {
    int i, k = getchar();
    if (k == EOF)
        return NULL;
    for (i = 0; k != EOF && k != '\n' && i < size; i++) {
        buff[i] = k;
        k = getchar();
        if (k == EOF && !feof(stdin))
            return NULL;
    }
    buff[i] = '\0';
    return buff;
}

int main(void) {

    char input[64];
    char dir[32] = "/bin/";
    char* args[32];
    char* lexeme;

    while (1) {
        sgets(input, 64);
        lexeme = strtok(input, " ");
        for (unsigned int i = 0; lexeme; i++) {
            args[i] = lexeme;
            lexeme = strtok(NULL, " ");
        }
        pid_t pid = fork();
        if (pid) {
            wait();
            for (unsigned int i = 0; i < 32; i++) {
                args[i] = NULL;
            }
        }
        else {
            if (execvp(strcat(dir, args[0]), args) == -1) {
                printf("Command not found\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    exit(EXIT_SUCCESS);
}