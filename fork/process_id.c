//fonte: Process IDs in C, CodeVault https://www.youtube.com/watch?v=PZrQ4eGm-hM&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=5 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
* It's important to protect pipe, ffork, write and read!!
*/
int	main()
{
	printf("My id before fork: %d\n", getpid());
	printf("----------------------------\n");
	int id = fork();
	int	res = wait(NULL);
	if (res != -1) //processo pai
	{
		printf("The child process %d finished your execution\n", res);
		printf("The parent process received from the fork the id: %d (that is from your son)\n", id); //o fork retorna para o processo pai o id do seu filho e 0 para o filho
		printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
	}
	else //processo filho
	{
		printf("No children to wait for, probably because I'm the child\n");
		printf("The child process received from the fork the id: %d\n", id); //0
		printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
		printf("----------------------------\n");
	}

	return (0);
}
