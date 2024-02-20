//fonte: Calling fork multiple times, https://www.youtube.com/watch?v=94URLRsjqMQ&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=6
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/*
* It's important to protect pipe, fork, write and read!!
*/
/*
* The wait() system call makes the parent process wait for any one of its child processes to terminate, not all of them.
* If successful, wait() returns the Process ID (PID) of the terminated child.
* Returns -1 if the calling process does not have any unwaited-for children and sets the errno variable. 
* This occurs when wait() is called by a process that either never had child processes, 
* or all of its children have already been waited for (i.e., there are no child processes left to wait for).
*/ 
int main()
{
	int	id1 = fork();
	int id2 = fork();
	pid_t child_pid;

	// this will gonna wait for all the child process to finish before their father
	// z e y sempre serão chamados antes de x, que por sua vez sempre será chamado antes do main
	// como são três filhos vamos entrar 3x nesse loop, até que o processo principal não terá filhos
	// e wait retornará -1
	while ((child_pid = wait(NULL)) != -1 || errno != ECHILD) //o pai fica parado aqui esperando no wait um filho terminar sua execução, o filho
		printf("I'm process %d and my child (%d) has just finished\n", getpid(), child_pid); //por sua vez nunca entra nesse while
		//porque o wait já de cara retorna -1. Quando o filho terminar, ele envia seu id pro wait que retorna para o pai que entra no while
		//e que depois volta a esperar no wait. Assim o pai fica no while até que todos seus filhos temrinem sua execução e então
	if (id1 == 0) //segue o fluxo do programa.
	{
		if (id2 == 0)
			printf("I'm the process y (%d)\n", getpid());
		else
			printf("I'm the process x (%d)\n", getpid());
	}
	else
	{
		if (id2 == 0)
			printf("I'm the process z (%d)\n", getpid());
		else
			printf("I'm the parent process (%d)\n", getpid());
	}
}
/* 
* To ensure a parent process waits until all of its child processes have terminated, 
* the parent must use wait() in a loop, calling it repeatedly until it returns -1, 
* indicating that there are no more child processes to wait for, like: while (wait(NULL) > 0);
* Porque o processo pai fica esperando. Um filho morre, o pai recebe seu id (maior que 0), entra 
* no while , depois volta pra condição do while e encontra o wait. Logo, o pai volta a esperar.
* Outro filho morre, wait retorna o id para o pai que entra no while, executa o while e volta
* pro wait. Se o pai não tem mais filhos então wait retorna -1, o pai não entra no while e 
* segue sua execução. Assim o pai esperou todos os filhos terminarem sua execução.
*/