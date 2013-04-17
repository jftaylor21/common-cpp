#include "utilities-mutex.h"

Utilities::Mutex::Mutex()
{
  pthread_mutex_init(&mMutex, 0);
}

Utilities::Mutex::~Mutex()
{
  unlock();
  pthread_mutex_destroy(&mMutex);
}

void Utilities::Mutex::lock()
{
  pthread_mutex_lock(&mMutex);
}

void Utilities::Mutex::unlock()
{
  pthread_mutex_unlock(&mMutex);
}

