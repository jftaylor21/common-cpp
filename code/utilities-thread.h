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
    void stop();
    void join();
    bool running() const;

  protected:
    virtual void run(){}

  private:
    //no copying!
    Thread(const Thread&);
    Thread& operator=(const Thread&);

    static void* createThread(void* args);

    bool mRunning;

  #ifdef WIN32
    HANDLE mThread;
  #else
    pthread_t mThread;
  #endif
  };
}

#endif

