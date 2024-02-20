//fonte https://www.youtube.com/watch?v=tcYo6hipaSA&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=2
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
* wait says: stop the execution until the child process has finished his execution 
* Com wait basicamente vc tem primeiro o filho sendo executado e depois o pai.
*/
int	main()
{
	int	id = fork(); //for the father process returns the pid of the newly created child process and for the child process returns 0. 
	int	n;
	int i;

	if (id == 0) //sou o processo filho
		n = 1;
	else
		n = 6;
	if (id != 0)
		wait(0); // o processo pai vai esperar pelo término do processo filho
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	return (0);
}
/*
* fflush:
* When performing input or output operations, C often uses buffering. 
* Instead of writing data directly to the destination (like a file or the terminal) 
* every time a write is requested, the data is temporarily stored in a buffer. 
* After the buffer is filled, or under certain conditions, the data is then 
* flushed to its destination. This buffering mechanism enhances performance 
* by reducing the number of direct write or read operations.

* The fflush() function is used to force the buffer to be written (flushed)
* to the destination before the buffer is full or before a normal flush would occur.
*/