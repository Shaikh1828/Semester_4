#include <stdlib.h> 	/* needed to define exit() */
#include <unistd.h> 	/* needed to define getpid() */
#include <stdio.h> 	/* needed for printf() */

int main() 
{
	printf("My Process ID is %d\n", getpid());	
	printf("My parent's Process ID is %d\n", getppid());
	exit(0);
}
