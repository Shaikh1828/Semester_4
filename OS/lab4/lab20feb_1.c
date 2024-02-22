#include<stdio.h>
#include<unistd.h>

int number = 0, n = 10 ;


void evenSum()
{
	int sum=0;
	number = 0;	
	for(int i=0;i<=n;i++)
	{
		if(number%2==0)
			sum+=number;
		number++;
	}
	
	printf("Sum of even numbers is: %d\n\n",sum);
}

void oddSum()
{
	int sum=0;
	number = 0;
	for(int i=0;i<=n;i++)
	{
		if(number%2!=0)
			sum+=number;
		number++;
	}
	
	printf("Sum of odd numbers is: %d\n\n",sum);
}


int main()
{
	int pid1 ;
	
	if( pid1 = fork() )
	{
		evenSum();
	}
	else
	{
		oddSum();
	}

	
}
