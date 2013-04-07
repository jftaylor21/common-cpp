#include "utilities-thread.h"

Utilities::Thread::Thread()
  : mRunning(false)
{
}

Utilities::Thread::~Thread()
{
  join();
}

void* Utilities::Thread::createThread(void* args)
{
  Thread* t(reinterpret_cast<Thread*>(args));
  if (t)
  {
    t->run();
  }
  return 0;
}
