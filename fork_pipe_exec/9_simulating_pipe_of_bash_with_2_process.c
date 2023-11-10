#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/*
* The same code of 8_simulating_pipe_of_bash but with just 2 process: the main executing 
* the grep and the child executing the ping.
*/
int main()
{
    int fd[2];
    
    if (pipe(fd) == -1)
        return (1);
    
    int pid1 = fork();
    if (pid1 == -1)
        return (2);
    
    if (pid1 == 0) //child process 1 - execute ping
    {
        // we want to reroute the stdout of our process 
        // ou seja, ao invés de printar na tela printar no fd1 (write) do pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); //fd de leitura não usamos
        close(fd[1]); //já temos o STDOUT_FILENO apontando para o mesmo lugar que fd[1] aponta que é o pipe
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }

    waitpid(pid1, NULL, 0);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
    execlp("grep", "grep", "round-trip", NULL); 
    return (0);
}