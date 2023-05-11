#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include "zemaphore.c"

int waiting_customer_count;
int waiting_room_capacity;
int total_capacity;//total capacity = waiting romm capacity + 1

int total_customers;
int total_customer_served;
int total_customer_arrived;
int total_customer_leaved;

int barber_has_come;

zem_t barber_zem; //act as conditional variable for barber
zem_t customer_zem; //act as conditional variable for customer
zem_t mutex; //act as a mutex lock

void *cut_hair()
{

  while(1)
  {
    zem_down(&mutex);
    barber_has_come = 1;  


    while(waiting_customer_count == 0)
    {
        printf("There is no customer.So barber is sleeping\n");
       // pthread_cond_wait(&barber_cond_var,&m);
        zem_up(&mutex);
        zem_down(&barber_zem);
        zem_down(&mutex);


    }


    
    printf("Barber served a customer\n");

    total_customer_served++;
    waiting_customer_count--;



    if((total_customer_served + total_customer_leaved) == total_customers)
    {
        zem_up(&customer_zem); //jar chul katse take signal dicche(the last person)

        zem_up(&mutex);
        zem_down(&barber_zem); //jar chul katse tar signal er jonno wait korche(the last person)
        zem_down(&mutex);


        printf("All customer serverd..So barber exits\n");
        zem_up(&mutex);
       

        break;
    }



    zem_up(&customer_zem); //jar chul katse take signal dicche
    
    zem_up(&mutex);
    zem_down(&barber_zem); //jar chul katse tar signal er jonno wait korche
    zem_down(&mutex);

    zem_up(&mutex);


  }



}

void *get_hair_cut(void *customer_id)
{
    int customer_thread_id = *((int *)customer_id);
    zem_down(&mutex);

    total_customer_arrived++;
    printf("Customer %d arrived in the barber shop\n",customer_thread_id);

    //if a customer thread is scheduled before the barber
    if(barber_has_come == 0)
    {
        printf("Barber has not come yet..So Customer %d is leaving\n",customer_thread_id);
        total_customer_leaved++;

    }

    else if(waiting_customer_count == 0)
    {
       zem_up(&barber_zem);
       printf("Customer %d got his turn\n",customer_thread_id);


       waiting_customer_count++;
       zem_up(&mutex);
       zem_down(&customer_zem);
       zem_down(&mutex);

       printf("Customer %d got a haircut\n",customer_thread_id);
       zem_up(&barber_zem);

    }
    else if(waiting_customer_count > 0 && waiting_customer_count < total_capacity)
    {
       waiting_customer_count++;
       printf("Barber is busy..So,Customer %d is waiting for his turn\n",customer_thread_id);
       printf("%d person is waiting in waiting room\n",waiting_customer_count-1); 


       zem_up(&mutex);
       zem_down(&customer_zem);
       zem_down(&mutex); 
       
       printf("Customer %d got his turn\n",customer_thread_id);
     
       printf("Customer %d got a haircut\n",customer_thread_id);


       zem_up(&barber_zem);


    }
    else
    {
        printf("Waiting room is full..So Customer %d is leaving\n",customer_thread_id);
        total_customer_leaved++;
    }

    zem_up(&mutex);

    


}




int main(int argc, char *argv[])
{
  
  
  total_customers=0;
  waiting_room_capacity=0;


  total_customer_arrived=0;
  total_customer_served=0;
  total_customer_leaved=0;
  waiting_customer_count=0;
  barber_has_come=0;

  pthread_t barber_thread;
  pthread_t *customer_thread;
  int *customer_thread_id;


  
  int i;
  
   if (argc < 3) {
    printf("Too few arguments.Try Again\n");
    exit(1);
  }
  else {

    total_customers = atoi(argv[1]);
    waiting_room_capacity = atoi(argv[2]);
    total_capacity = waiting_room_capacity + 1;
  }
  

  zem_init(&barber_zem,0);
  zem_init(&customer_zem,0);

  zem_init(&mutex,1);

  

    

   //waiting_buffer_queue = (int *)malloc (sizeof(int) * waiting_room_capacity);

   //creating barber_thread
    pthread_create(&barber_thread, NULL, cut_hair, NULL);


   //creating customer threads
   customer_thread = (pthread_t *)malloc(sizeof(pthread_t) * total_customers);

   customer_thread_id = (int *)malloc(sizeof(int) * total_customers);
   
   for (i = 0; i < total_customers; i++)
    customer_thread_id[i] = i;

   for (i = 0; i < total_customers; i++)
    pthread_create(&customer_thread[i], NULL, get_hair_cut, (void *)&customer_thread_id[i]);


  //joining barber thread 
  pthread_join(barber_thread,NULL);
  printf("Barber joined\n");


  //joining customer threads
  for (i = 0; i < total_customers; i++)
    {
      pthread_join(customer_thread[i], NULL);
      printf("customer %d joined\n", i);
    }
  
  /*----Deallocating heap memory---------------------*/

  //My code starts
  free(customer_thread);
  free(customer_thread_id);
  
  //My code ends
  
  return 0;
}
