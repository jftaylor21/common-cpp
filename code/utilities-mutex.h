#ifndef UTILITIES_MUTEX_H
#define UTILITIES_MUTEX_H

#ifdef WIN32
  #include <windows.h>
#else
  #include <pthread.h>
#endif

namespace Utilities
{
  class Mutex
  {
  public:
    Mutex();
    virtual ~Mutex();

    void lock();
    void unlock();

  private:
  #ifdef WIN32
    HANDLE mMutex;
  #else
    pthread_mutex_t mMutex;
  #endif
  };
}

#endif

