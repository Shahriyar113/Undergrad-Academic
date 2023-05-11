#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  //	Write the code for initializing your read-write lock.
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

  //Increase the number of current readers to handle
  rw->num_of_readers++;

  //If a writer is writing currently the reader can not
  //get access. So wait.
  while(rw->currently_writing){
    pthread_cond_wait(&rw->read, &rw->mutex);
  }

  pthread_mutex_unlock(&rw->mutex);
}

void ReaderUnlock(struct read_write_lock * rw)
{
  //	Write the code for releasing read-write lock by the reader.
  pthread_mutex_lock(&rw->mutex);

  // Reading complete. So decrease the number of current readers.
  rw->num_of_readers--;

  // If there is no reader waiting to read then signal a random writer.
  if(rw->num_of_readers == 0){
    pthread_cond_signal(&rw->write);
  }

  pthread_mutex_unlock(&rw->mutex);
}

void WriterLock(struct read_write_lock * rw)
{
  //	Write the code for aquiring read-write lock by the writer.
  pthread_mutex_lock(&rw->mutex);

  // If at least one reader is currently (reading or waiting) OR 
  // one writer is currently writing then wait.
  while(rw->num_of_readers > 0 || rw->currently_writing){
    pthread_cond_wait(&rw->write, &rw->mutex);
  }

  // Set status to be currently writing.
  rw->currently_writing = true;

  pthread_mutex_unlock(&rw->mutex);
}

void WriterUnlock(struct read_write_lock * rw)
{
  //Write the code for releasing read-write lock by the writer.
  pthread_mutex_lock(&rw->mutex);

  // Set the status to Not currently writing
  rw->currently_writing = false;

  // Wake up all readers from sleep who were sleeping due to currently
  // writing status. 
  pthread_cond_broadcast(&rw->read);

  // Wake up a random writer from sleep who were sleeping due to
  // currently writing status if there is no reader waiting to read.
  if(rw->num_of_readers == 0){
    pthread_cond_signal(&rw->write);
  }
  pthread_mutex_unlock(&rw->mutex);
}
