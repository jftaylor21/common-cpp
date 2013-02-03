#include "utilities-mutex.h"

Utilities::Mutex::Mutex()
  : mMutex(CreateMutex(0, false, 0))
{
}

Utilities::Mutex::~Mutex()
{
  CloseHandle(mMutex);
}

void Utilities::Mutex::lock()
{
  WaitForSingleObject(mMutex, INFINITE);
}

void Utilities::Mutex::unlock()
{
  ReleaseMutex(mMutex);
}
