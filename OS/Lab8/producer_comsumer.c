#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define bufferSize 10

void *produce(void *parameter);
void *consume(void *parameter);

sem_t empty, mutex, full;
int buffer[bufferSize], in, out;


int main()
{
    int thread_size = 1 ;
    pthread_t producer, consumer;
    pthread_attr_t attr;

    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    
    pthread_attr_init(&attr);

    int i;
    for( i = 0; i < 10; i++ )
    {
        pthread_create(&producer, &attr, produce, NULL);
        pthread_create(&consumer, &attr, consume, NULL);
    }
    
    for( i = 0; i < thread_size; i++ )
    {
        pthread_join(producer, NULL);
        pthread_join(consumer, NULL);
    }

    sem_destroy(&empty) ;
    sem_destroy(&full) ;
    sem_destroy(&mutex) ;

    return 0 ;
}

void *produce(void *parameter)
{
    int item;
    item = rand()%20 ;
    sem_wait(&empty) ;
    sem_wait(&mutex) ;
    buffer[in] = item ;
    printf("Produced item %d at index %d\n", item, in ) ;
    in = (in+1)%bufferSize ;
    sem_post(&mutex) ;
    sem_post(&full) ;
}

void *consume(void *parameter)
{
    int item ;
    sem_wait(&full) ;
    sem_wait(&mutex) ;
    item=buffer[out] ;
    printf("Consumed item %d from from %d\n", item, out) ;
    out = (out+1)%bufferSize ;
    sem_post(&mutex) ;
    sem_post(&empty) ;
}