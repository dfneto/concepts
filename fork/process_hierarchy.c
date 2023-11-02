//fonte: Calling fork multiple times, https://www.youtube.com/watch?v=94URLRsjqMQ&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=6
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/*
* It's important to protect pipe, ffork, write and read!!
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
	while ((child_pid = wait(NULL)) != -1 || errno != ECHILD)
		printf("I'm process %d and my child (%d) has just finished\n", getpid(), child_pid);
	if (id1 == 0)
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