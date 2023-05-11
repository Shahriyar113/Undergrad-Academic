#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include "zemaphore.h"

void zem_init(zem_t *s, int value) {

    //My_code_start
    //initializing both "mutex and cond"
    pthread_mutex_init(&s->m,NULL);
    pthread_cond_init(&s->c,NULL);

    s->zemaphore_count = value;
    //My_code_end
  
}

void zem_down(zem_t *s) {
   //My_code_start
   pthread_mutex_lock(&s->m);

    s->zemaphore_count--;
    if(s->zemaphore_count < 0)
    {
        pthread_cond_wait(&s->c,&s->m);
    }



    pthread_mutex_unlock(&s->m);
    //My_code_end
}

void zem_up(zem_t *s) {
    //My_code_start
    pthread_mutex_lock(&s->m);
    s->zemaphore_count++;
    pthread_cond_signal(&s->c);
    pthread_mutex_unlock(&s->m);
    //My_code_ends
}


