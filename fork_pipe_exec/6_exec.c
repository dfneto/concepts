//fonte https://www.youtube.com/watch?v=OVFEWSP7n8c&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=14
#include <unistd.h>
#include <stdio.h>

int main()
{
	execlp("ping", "ping", "-c", "3", "google.com", NULL);
	printf("THIS SHOULD NOT BE PRINTED ON THE TERMINAL!"); //it's not executed unless you have an error in exec
	return (0);
}