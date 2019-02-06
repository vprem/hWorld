#include<stdio.h>
#include<pthread.h>

pthread_t tid[2];
unsigned int shared_data = 0;
pthread_mutex_t mutex;
unsigned int rc;
//prototypes for callback functions

void* PrintEvenNos(void*);
void* PrintOddNos(void*);

void main(void)
{
    pthread_create(&tid[0],0,&PrintEvenNos,0);
    pthread_create(&tid[1],0,&PrintOddNos,0);

    while(1)
    {
       sleep(3);
       pthread_mutex_lock(&mutex);
       
       if(shared_data>10)
       {
         exit(0);
       }
      rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
}

void* PrintEvenNos(void *ptr)
{
    while (1)
    {
     sleep(2);
    pthread_mutex_lock(&mutex);
    if(shared_data%2 == 0)
    {
       printf("Even:%d\n",shared_data);
       shared_data++;
    }
    rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
    }
}

void* PrintOddNos(void* ptr1)
{
    while(1)
    {
      sleep(2);
    rc = pthread_mutex_lock(&mutex);
    if(shared_data%2 != 0)
    {
        printf("odd:%d\n",shared_data);
        shared_data++;
    } 
    rc = pthread_mutex_unlock(&mutex);//if number is even, do not print, release mutex 
    }
}
