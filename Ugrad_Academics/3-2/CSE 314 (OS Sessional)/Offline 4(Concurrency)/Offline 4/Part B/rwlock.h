#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

struct read_write_lock
{
    pthread_mutex_t mutex;
    pthread_cond_t read;
    pthread_cond_t write;
    /*IMPORTANT*/
    /*   
            num_of_readers is used as the number of current+waiting readers for reader preference section
            num_of_readers is used as the number of current readers for writer preference section
    */
    /*IMPORTANT*/
    int num_of_readers;
    int num_of_waiting_writers;
    bool currently_writing;
};

void InitalizeReadWriteLock(struct read_write_lock * rw);
void ReaderLock(struct read_write_lock * rw);
void ReaderUnlock(struct read_write_lock * rw);
void WriterLock(struct read_write_lock * rw);
void WriterUnlock(struct read_write_lock * rw);
