//fonte https://www.youtube.com/watch?v=OVFEWSP7n8c&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=14 How to execute another program in C (using exec)
//https://github.com/dfneto/concepts/blob/main/fork_pipe_exec/6_exec.c
#include <unistd.h>
#include <stdio.h>

int main()
{
	execlp("ping", "ping", "-c", "3", "google.com", NULL);
	printf("THIS SHOULD NOT BE PRINTED ON THE TERMINAL!"); //it's not executed unless you have an error in exec
	return (0);
	//para eu fazer algo no mesmo programa (creio que no mesmo processo também) eu devo fazer um fork: https://github.com/dfneto/concepts/blob/main/fork_pipe_exec/7_exec_comands.c
}
/*
A função execlp executa arquivos executáveis, programas (.exe no windows), 
e não scripts ou comandos. O que exec faz é executar diretamente o arquivo 
executável, ou seja, C busca no PATH o executável e o executa. Assim, não 
podemos fazer um grep ou rodar algum script, como: 

execlp("ping", "ping", "-c", "3", "google.com", "|", "grep", "rtt", NULL);

Bash entende o comando acima, sabe o que é pipe. Mas o execlp vê o pipe, 
grep e o rtt como argumentos do ping.

*/