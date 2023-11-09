//fonte: https://www.youtube.com/watch?v=6xbLgZpOBi8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=24
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

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

//TODO: tentar executar isso no pai
    int pid2 = fork();
    if (pid2 == -1)
        return (3);
    if (pid2 == 0) //child process 2 - execute grep
    {
        dup2(fd[0], STDIN_FILENO); //quero que a entrada do processo seja o read do pipe
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "round-trip", NULL); 
        //como a saída deste processo não mudou (stdout) devemos ver a saída do comando na tela
    }

    /* 
        grep fica constantemente lendo do stdin (que neste caso é o pipe), esperando por inputs,
        até que todos os writers (fd1) sejam fechados. Já fechamos eles nos processos filhos e
        o linux fechou automaticamente o STDOUT (something nice about Linux processes is
        that they close their STD out once they're finished), So once ping has finished its 
        execution, it automatically closes this duplicated file descriptor of fd[1]: dup2(fd[1], STDOUT_FILENO);
        falta fechar o writer do main (fechamos por boa prática o reader tbm) 
    */
    close(fd[0]);
    close(fd[1]);

    // Ensure that the parent process waits for the childs before it exits.
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}