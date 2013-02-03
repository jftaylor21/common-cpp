#include "utilities-thread.h"

void Utilities::Thread::start()
{
  mRunning = true;
  pthread_create(&mThread, 0, createThread, this);
}

void Utilities::Thread::join()
{
  mRunning = false;
  pthread_join(mThread, 0);
}


