#include "utilities-thread.h"

void Utilities::Thread::start()
{
  mRunning = true;
  mThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(createThread), this, 0, 0);
}

void Utilities::Thread::join()
{
  stop();
  WaitForSingleObject(mThread, INFINITE);
  CloseHandle(mThread);
}
