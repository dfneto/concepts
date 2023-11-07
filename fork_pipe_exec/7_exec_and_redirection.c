// fonte: https://www.youtube.com/watch?v=uh2FqejQRk8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=13 executing commands
// and https://www.youtube.com/watch?v=DiNmwwQWl0g&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12 getting exit status
// and https://www.youtube.com/watch?v=5fnVr-zH-SE&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=19 redirecting standard output
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
* It's important to protect pipe, fork, write and read!!
*/

/*
* We are going to execute a command and redirect his output to a file in the child process 
* and in the main process we are going to get the status of what happend in the child
*/
int main()
{
	int	pid = fork(); 
	if (pid == -1)
		return (1);
	if (pid == 0) //child process - execute the program
	{
		int file = open("output.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (2);
		
		/* uncomment to understand dup
		int file2 = dup(file);//returns another FD to our output.txt
		printf("file1: %d, file2: %d\n", file, file2); //file1: 3, file2: 4
		*/

		printf("I'm the child and I'm executing the ping program ... \nAll the output of the program will be saved in the output.txt file. Go there to check ;)\n");

		dup2(file, STDOUT_FILENO); //close stdout and set fd1 to pingResults.txt
		close(file);

		printf("This message came from the the child and this is the status of the file executed in the child process as well ...\n");
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL); //o exec não muda nem o process id nem os FDs.
		if (err == -1)
		{
			printf("Could not find the program to execute\n");
			return (3);
		}
	}
	else	//main process  - get the status of the child
	{
		int wait_status;
		wait(&wait_status); //the parameter of wait give us some information of what happened with the child process
		if (WIFEXITED(wait_status))
		{
			printf("...................\n\n\nI'm the main process and the child got: ");
			int status_code = WEXITSTATUS(wait_status);
			if (status_code == 0)
				printf("Sucess!\n");
			else
				printf("Failure with status code %d!\n", status_code);
		}
		printf("Some post processing goes here!\n");
	}


}