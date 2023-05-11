#include <pthread.h>


typedef struct zemaphore {
    //My_code_start
    pthread_cond_t c ;
    pthread_mutex_t m ;
    int zemaphore_count;

    //My_code_ends
} zem_t;

void zem_init(zem_t *, int);
void zem_up(zem_t *);
void zem_down(zem_t *);




