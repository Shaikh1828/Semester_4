#include <stdlib.h> 	/* needed to define exit() */
#include <unistd.h> 	/* needed to define getpid() */
#include <stdio.h> 	/* needed for printf() */
int main() 
{
	printf("About to run ls\n");
	execlp("ls", "ls", "-aF", "/", (char*)0);
	perror("execlp"); /* if we get here, execlp failed */
	exit(1);
}
