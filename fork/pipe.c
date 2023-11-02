#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd[2];
	printf("%d\n", fd[0]);
	printf("%d\n", fd[1]);
	pipe(fd);
	printf("%d\n", fd[0]);
	printf("%d\n", fd[1]);

}