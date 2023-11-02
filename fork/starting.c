#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * When performing input or output operations, C often uses buffering. Instead of writing data directly to the destination (like a file or the terminal) every time a write is requested, the data is temporarily stored in a buffer. After the buffer is filled, or under certain conditions, the data is then flushed to its destination. This buffering mechanism enhances performance by reducing the number of direct write or read operations.

* The fflush() function is used to force the buffer to be written (flushed) to the destination before the buffer is full or before a normal flush would occur.
*/
/*
 *the **`wait()`** function is a system call used to make the parent process wait until all of its child processes have terminated.

- If successful, **`wait()`** returns the Process ID (PID) of the terminated child.
- If the calling process has no child processes, **`wait()`** returns **`1`**.
Com wait basicamente vc tem primeiro o filho sendo executado e depois o pai.
 */
int	main()
{
	int	id = fork();
	int	n;
	int i;

	if (id == 0) //sou o processo filho
		n = 1;
	else
		n = 6;
	wait(0); //o filho retorna -1, o pai retorna o id do processo filho encerrado, assim que tem que esperar pelo filho encerrar
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	return (0);
}
