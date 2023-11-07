// fonte: https://www.youtube.com/watch?v=uh2FqejQRk8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=13 
// and https://www.youtube.com/watch?v=DiNmwwQWl0g&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/*
* It's important to protect pipe, ffork, write and read!!
*/

/*
* 
*/
int main()
{
	int	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0) //child process 
	{
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find the program to execute\n");
			return 2;
		}
	}
	else	//main process 
	{
		int wait_status;
		wait(&wait_status); //the parameter of wait give us some information of what happened with the child process
		if (WIFEXITED(wait_status))
		{
			int status_code = WEXITSTATUS(wait_status);
			if (status_code == 0)
				printf("Sucess!\n");
			else
				printf("Failure with status code %d!\n", status_code);
		}
		printf("Success!\n");
	}


}