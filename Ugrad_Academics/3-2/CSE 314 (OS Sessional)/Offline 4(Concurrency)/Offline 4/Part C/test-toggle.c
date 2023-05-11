#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include "zemaphore.h" //My code

//In this file..all "zemaphore" related code is my modification

#define NUM_THREADS 3
#define NUM_ITER 10

zem_t z[NUM_THREADS]; //3 zemaphores for 3 threads


void *justprint(void *data)
{
  int thread_id = *((int *)data);

  for(int i=0; i < NUM_ITER; i++)
    {
      //Here ,"thread 0" will print once...then it will sleep and wake up "thread 1" 
      //Here ,"thread 1" will print once...then it will sleep and wake up "thread 2" 
      //Here ,"thread 2" will print once...then it will sleep and wake up "thread 0" 
      //for this circular addressing "thread_id+1)%NUM_THREADS" is used


      zem_down(&z[thread_id]); //My code
      printf("This is thread %d\n", thread_id);
      zem_up(&z[(thread_id+1)%NUM_THREADS]); //My code

      

    }
  return 0;
}

int main(int argc, char *argv[])
{

  pthread_t mythreads[NUM_THREADS];
  int mythread_id[NUM_THREADS];

  //initializing all zemaphores

  //initial value of 1st thread's(thread 0) zemaphore = 1 so that "thread 0" always print first
    zem_init(&z[0],1); 

  for(int i =1; i < NUM_THREADS; i++)
  {
    zem_init(&z[i],0);
  }

  
  for(int i =0; i < NUM_THREADS; i++)
    {
      mythread_id[i] = i;
      pthread_create(&mythreads[i], NULL, justprint, (void *)&mythread_id[i]);
    }
  
  for(int i =0; i < NUM_THREADS; i++)
    {
      pthread_join(mythreads[i], NULL);
    }
  
  return 0;
}
