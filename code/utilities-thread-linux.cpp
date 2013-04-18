#include "utilities-thread.h"

void Utilities::Thread::start()
{
  mRunning = true;
  pthread_create(&mThread, 0, createThread, this);
}

void Utilities::Thread::join()
{
  stop();
  pthread_join(mThread, 0);
}

long Utilities::Thread::currentThreadID()
{
  return gettid();
}
