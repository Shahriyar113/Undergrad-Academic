#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  //Write the code for initializing your read-write lock.
  pthread_mutex_init(&rw->mutex, NULL);
  pthread_cond_init(&rw->read, NULL);
  pthread_cond_init(&rw->write, NULL);
  rw->num_of_readers = 0;
  rw->num_of_waiting_writers = 0;
  rw->currently_writing = false;
}

void ReaderLock(struct read_write_lock * rw)
{
  //Write the code for aquiring read-write lock by the reader.
  pthread_mutex_lock(&rw->mutex);

  // if there is a writer currently writing OR 
  // a number of writers waiting to write then 
  // reader should wait
  while(rw->currently_writing || rw->num_of_waiting_writers > 0){
    pthread_cond_wait(&rw->read, &rw->mutex);
  }

  // Increase the number of readers in system. For writer preference there 
  // is only current readers, no waiting readers
  rw->num_of_readers++;

  pthread_mutex_unlock(&rw->mutex);
}

void ReaderUnlock(struct read_write_lock * rw)
{
  //	Write the code for releasing read-write lock by the reader.
  pthread_mutex_lock(&rw->mutex);

  // Decrease the number of current readers in system.
  rw->num_of_readers--;

  // Signal all the writers who were sleeping because of this reader
  // Check if there is any current reader left.
  // If not then wake up all the writers.
  if(rw->num_of_readers == 0){
    pthread_cond_signal(&rw->write);
  }
  pthread_mutex_unlock(&rw->mutex);
}

void WriterLock(struct read_write_lock * rw)
{
  //	Write the code for aquiring read-write lock by the writer.
  pthread_mutex_lock(&rw->mutex);

  // Increase the number of waiting writers
  rw->num_of_waiting_writers++;

  // If at least one reader is currently (reading or waiting) OR
  // one writer is currently writing then wait.
  while(rw->num_of_readers > 0 || rw->currently_writing){
    pthread_cond_wait(&rw->write, &rw->mutex);
  }

  // Set status to be currently writing.
  rw->currently_writing = true;

  // Decrease the number of waiting writers
  rw->num_of_waiting_writers--;
  pthread_mutex_unlock(&rw->mutex);
}

void WriterUnlock(struct read_write_lock * rw)
{
  //	Write the code for releasing read-write lock by the writer.
  pthread_mutex_lock(&rw->mutex);

  // Set status to be currently not writing.
  rw->currently_writing = false;

  // If there is a writer waiting then signal a random writer.
  if(rw->num_of_waiting_writers > 0)
    pthread_cond_signal(&rw->write);

  // If there is no writer waiting then signal all the readers.
  else pthread_cond_broadcast(&rw->read);

  pthread_mutex_unlock(&rw->mutex);
}
