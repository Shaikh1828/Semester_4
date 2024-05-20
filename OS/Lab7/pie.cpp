#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double random_value1, random_value2, dis;
int inside = 0 ;
void *runner(void *param);                    /* the thread */


double distance ( double a, double b)
{
	return sqrt( a*a + b*b ) ;
}

int main(int argc, char *argv[])
{
    int total = 20000 ;
    pthread_t tid[total];                    /* the thread identifier */
    pthread_attr_t attr;                    /* set of attributes for the thread */

    if (argc != 2) 
    {
        fprintf(stderr,"usage: a.out <integer value>\n");
        /*exit(1);*/
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        /*exit(1);*/
        return -1;
    }

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */

    for ( int i = 0; i < total; i++ )
    {
        pthread_create(&tid[i],&attr,runner, NULL);
    }
    
    /* now wait for the thread to exit */
    for( int i = 0; i < total; i++ )
    {
        
        pthread_join(tid[i],NULL);

    }

    printf("%lf  \n", (double)inside*4/total );

}

void *runner(void *param) 
{
    random_value1 = (double)rand()/RAND_MAX*2.0-1.0; 
    random_value2 = (double)rand()/RAND_MAX*2.0-1.0;

    dis = distance( random_value1, random_value2 );
    if ( dis < 1 ) 
    {
        inside ++;
    }

	pthread_exit(0);
}