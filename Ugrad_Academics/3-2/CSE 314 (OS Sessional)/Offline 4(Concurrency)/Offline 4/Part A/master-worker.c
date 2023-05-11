#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>

int item_to_produce, curr_buf_size,consumed_item,total_item_consumed;
int total_items, max_buf_size, num_workers, num_masters;

int *buffer;


pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void print_produced(int num, int master) {

  printf("Produced %d by master %d\n", num, master);
}

void print_consumed(int num, int worker) {

  printf("Consumed %d by worker %d\n", num, worker);
  
}


//produce items and place in buffer
//modify code below to synchronize correctly
void *generate_requests_loop(void *data)
{
  int thread_id = *((int *)data);

  while(1)
    {
      //My code starts
      pthread_mutex_lock(&m);
      
      if(item_to_produce >= total_items) {

        //if all items are produced then the master threads should exit
        pthread_mutex_unlock(&m);
	      break;
      }

      //if buffer is not full then the master can produce an item
      while(curr_buf_size >= max_buf_size )
      {
        //if buffer is full and all items are produced that means there is no hope to produce
        //so no need to wait
         if(item_to_produce < total_items)
            pthread_cond_wait(&empty,&m);
         else
            break;
      }

      //after waking up and seeing all items are produced..there is no hope to produce.so bye bye

      if(item_to_produce >= total_items)
      {
        //if all items produced by the producer are consumed then the consumer threads should exit
        pthread_mutex_unlock(&m);
        break;

      }
 
      buffer[curr_buf_size++] = item_to_produce;
      print_produced(item_to_produce, thread_id);
      item_to_produce++;

       //after producing an item all the consumers should wake up..

      //if we wake up one consumer then  it can be happened that after producing all the items
      //there are some consumers remains sleeping all the time 

      pthread_cond_broadcast(&full);
      
      pthread_mutex_unlock(&m);

      //My code ends
    }
  return 0;
}

//write function to be run by worker threads
//ensure that the workers call the function print_consumed when they consume an item

//My code starts

void *consume_requests_loop(void *data)
{
  int thread_id = *((int *)data);

  while(1)
    {
      //My code starts
      pthread_mutex_lock(&m);

      if(total_item_consumed>=total_items)
      {
        //if all items produced by the producer are consumed then the consumer threads should exit
        pthread_mutex_unlock(&m);
        break;

      }

      while(curr_buf_size == 0)
      {
        //if buffer is empty and all items are consumed that means there is no hope to consume
        //so no need to wait
        if(total_item_consumed < total_items) 
           pthread_cond_wait(&full,&m);
        else
            break;   

        
      }

      //after waking up and seeing all items are consumed..there is no hope to consume.so bye bye

      if(total_item_consumed >= total_items)
      {
        //if all items produced by the producer are consumed then the consumer threads should exit
        pthread_mutex_unlock(&m);
        break;

      }



      consumed_item = buffer[--curr_buf_size];
      print_consumed(consumed_item, thread_id);
      total_item_consumed++;

      //after consuming an item all the producers should wake up..

      //if we wake up one producer then  it can be happened that after consuming all the items
      //there are some producers remains sleeping all the time 
      

      pthread_cond_broadcast(&empty);

      pthread_mutex_unlock(&m);

     

    }

      

  


}



//My code ends



int main(int argc, char *argv[])
{
  int *master_thread_id;
  int *worker_thread_id;

  pthread_t *master_thread;
  pthread_t *worker_thread;

  item_to_produce = 0;
  curr_buf_size = 0;
  consumed_item=0;
  total_item_consumed=0;
  
  int i;
  
   if (argc < 5) {
    printf("./master-worker #total_items #max_buf_size #num_workers #masters e.g. ./exe 10000 1000 4 3\n");
    exit(1);
  }
  else {
    num_masters = atoi(argv[4]);
    num_workers = atoi(argv[3]);
    total_items = atoi(argv[1]);
    max_buf_size = atoi(argv[2]);
  }
    

   buffer = (int *)malloc (sizeof(int) * max_buf_size);

   //create master producer threads
   master_thread_id = (int *)malloc(sizeof(int) * num_masters);
   master_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_masters);
  for (i = 0; i < num_masters; i++)
    master_thread_id[i] = i;

  for (i = 0; i < num_masters; i++)
    pthread_create(&master_thread[i], NULL, generate_requests_loop, (void *)&master_thread_id[i]);
  
  //create worker consumer threads
  //My code starts

   worker_thread_id = (int *)malloc(sizeof(int) * num_workers);
   worker_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_workers);
  for (i = 0; i < num_workers; i++)
    worker_thread_id[i] = i;

  for (i = 0; i < num_workers; i++)
    pthread_create(&worker_thread[i], NULL, consume_requests_loop, (void *)&worker_thread_id[i]);
  //My code end

  
  //wait for all threads to complete

  
  //joining master threads
  for (i = 0; i < num_masters; i++)
    {
      pthread_join(master_thread[i], NULL);
      printf("master %d joined\n", i);
    }
  
    //My code starts

  //joining worker threads
  for (i = 0; i < num_workers; i++)
    {
      pthread_join(worker_thread[i], NULL);
      printf("worker %d joined\n", i);
    }


    //My code ends
  
  /*----Deallocating Buffers---------------------*/
  free(buffer);
  free(master_thread_id);
  free(master_thread);

  //My code starts
  free(worker_thread);
  free(worker_thread_id);
  
  //My code ends
  
  return 0;
}
