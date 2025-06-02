#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    int pid;

    pid = fork();

    if (pid < 0)
    {
        perror("Erro: ");
        exit(-1);
    }
    else if (pid > 0)
        wait(0);
    else
    {

        execve("/bin/date", argv, envp);
        perror("Erro: ");
    }
    printf("Tchau !\n");
    exit(0);
}