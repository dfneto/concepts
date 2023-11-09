//fonte https://www.youtube.com/watch?v=Mqb2dVRe0uo&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=7
#include <unistd.h>
#include <stdio.h>

/*
* It's important to protect pipe, fork, write and read!!
*/

/*
* In this example the child process will write in the pipe
* and the main process will read from the pipe
*/
int main()
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		printf("An error ocurred with opening the pipe.\n");
		return 1;
	}
	printf("fd0 - to read: %d\n", fd[0]);
	printf("fd1 - to write: %d\n", fd[1]);
	
	int	id = fork();
	if (id == 0) //child process will write to the pipe
	{
		close(fd[0]);
		int x;
		printf("Input a number to be write in pipe (child process says):\n");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else	//main process will read from the pipe
	{
		close(fd[1]);
		int x;
		read(fd[0], &x, sizeof(int));
		close(fd[0]);
		printf("The number readed from the pipe is (main process says): %d", x);
	}

}