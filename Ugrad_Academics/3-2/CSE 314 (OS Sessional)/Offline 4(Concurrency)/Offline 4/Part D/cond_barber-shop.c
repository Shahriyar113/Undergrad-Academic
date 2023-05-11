#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>

pthread_cond_t barber_cond_var = PTHREAD_COND_INITIALIZER;
pthread_cond_t waiting_customer_queue = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int waiting_customer_count;
int waiting_room_capacity;
int total_capacity;//total capacity = waiting romm capacity + 1

int barber_has_come;

int total_customers;
int total_customer_served;
int total_customer_arrived;
int total_customer_leaved;



void *cut_hair()
{

  while(1)
  {
     pthread_mutex_lock(&m);
     barber_has_come=1;

    while(waiting_customer_count == 0)
    {
        printf("There is no customer.So barber is sleeping\n");
        pthread_cond_wait(&barber_cond_var,&m);
    }


    
    printf("Barber served a customer\n");
    total_customer_served++;
    waiting_customer_count--;



    if((total_customer_served + total_customer_leaved) == total_customers)
    {
        pthread_cond_signal(&waiting_customer_queue); //jar chul katse take signal dicche(the last person)
        pthread_cond_wait(&barber_cond_var,&m); //jar chul katse tar signal er jonno wait korche(the last person)

        printf("All customer serverd..So barber exits\n");

        pthread_mutex_unlock(&m);

        break;
    }



    pthread_cond_signal(&waiting_customer_queue); //jar chul katse take signal dicche
    
    pthread_cond_wait(&barber_cond_var,&m); //jar chul katse tar signal er jonno wait korche
    pthread_mutex_unlock(&m);


  }



}

void *get_hair_cut(void *customer_id)
{
    int customer_thread_id = *((int *)customer_id);
    pthread_mutex_lock(&m);

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
       pthread_cond_signal(&barber_cond_var);
       printf("Customer %d got his turn\n",customer_thread_id);
       waiting_customer_count++;
       pthread_cond_wait(&waiting_customer_queue,&m);

       printf("Customer %d got a haircut\n",customer_thread_id);
       pthread_cond_signal(&barber_cond_var);

    }
    else if(waiting_customer_count > 0 && waiting_customer_count < total_capacity)
    {
       waiting_customer_count++;
       printf("Barber is busy..So,Customer %d is waiting for his turn\n",customer_thread_id);

       //karon customer er hair cut er por "waiting_customer_count" decrease hocche
       printf("%d person is waiting in waiting room\n",waiting_customer_count-1); 


       pthread_cond_wait(&waiting_customer_queue,&m);
       printf("Customer %d got his turn\n",customer_thread_id);

       printf("Customer %d got a haircut\n",customer_thread_id);


       pthread_cond_signal(&barber_cond_var);


    }
    else
    {
        printf("Waiting room is full..So Customer %d is leaving\n",customer_thread_id);
        total_customer_leaved++;
    }
    
    pthread_mutex_unlock(&m);

    



}




int main(int argc, char *argv[])
{
  
  total_customers=0;
  waiting_room_capacity=0;
  barber_has_come=0;


  total_customer_arrived=0;
  total_customer_served=0;
  total_customer_leaved=0;
  waiting_customer_count=0;

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
    total_capacity = waiting_room_capacity +1;
  }
  

    

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
