#ifndef UTILITIES_THREAD_H
#define UTILITIES_THREAD_H

#ifdef WIN32
  #include <windows.h>
#else
  #include <pthread.h>
#endif

namespace Utilities
{
  class Thread
  {
  public:
    Thread();
    virtual ~Thread();

    void start();
    void join();

  protected:
    virtual void run(){}
    bool mRunning;

  private:
    static void* createThread(void* args);

  #ifdef WIN32
    HANDLE mThread;
  #else
    pthread_t mThread;
  #endif
  };
}

#endif

