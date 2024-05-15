#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define reader_num 5
#define writer_num 1

sem_t mutex, rw_mutex;
int readers_count = 0;

int shared_data;

void init_semaphores();
void *reader(void *arg);
void *writer(void *arg);
void destroy_semaphores();

int main() 
{
    pthread_t readers[reader_num], writers[writer_num];
    int reader_ids[reader_num], writer_ids[writer_num];
    
    init_semaphores();
    
    for (int i = 0; i < reader_num; i++) 
    {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    for (int i = 0; i < writer_num; i++) 
    {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    for (int i = 0; i < reader_num; i++) 
    {
        pthread_join(readers[i], NULL);
    }
    
    for (int i = 0; i < writer_num; i++) 
    {
        pthread_join(writers[i], NULL);
    }
    
    destroy_semaphores();
    
    return 0;
}

void init_semaphores()
{
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
}

void *reader(void *arg) 
{
    int id = *(int *)arg;
    
    while (1) 
    {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) 
        {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex); 

        printf("Reader %d reads the value of the shared data: %d, readers count : %d\n", id, shared_data, readers_count);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) 
        {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex); 

        sleep(rand()%5);
    }
    return NULL;
}

void *writer(void *arg) 
{
    int id = *(int *)arg;
    
    while (1) 
    {
        sem_wait(&rw_mutex);
        
        shared_data = rand() % 100; 

        printf("Writer %d writes the value %d in the shared data\n", id, shared_data);
        
        sem_post(&rw_mutex);

        sleep(rand()%5);
    }
    return NULL;
}

void destroy_semaphores()
{
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
}