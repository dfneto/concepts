//fonte: https://www.youtube.com/watch?v=6u_iPGVkfZ4&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=8
#include <unistd.h>
#include <stdio.h>

/*
* It's important to protect pipe, fork, write and read!!
*/

/*
* In this exercise we are going to split an array 
* and sum each half in a process and in the end
* sum the 2 sums 
*/
int main()
{
	int arr[] = { 1, 2, 3, 4, 1, 2};
	int	arrLen = sizeof(arr)/ sizeof(int);
	int start, end;
	int fd[2];
	int	id;

	pipe(fd);
	id = fork();

	if (id == 0) //child process will sum half of the array
	{
		start = 0;
		end = arrLen / 2;
	}
	else	//main process will sum the other half of the array
	{
		start = arrLen / 2;
		end = arrLen;
	}

	int sum = 0;
	int i;
	for (i = start; i < end; i++)
		sum += arr[i];
	
	printf("Calculated partial sum: %d\n", sum);

	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		// Wait for the child process to complete
    	wait(NULL);
		
		int sum_from_child;
		close(fd[1]);
		read(fd[0], &sum_from_child, sizeof(sum_from_child));
		close(fd[0]);

		int total_sum = sum + sum_from_child;
		printf("Total sum: %d\n", total_sum);
	}

}