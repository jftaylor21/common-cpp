#include "utilities-socket.h"

Utilities::Socket::Socket(SocketType type)
  : mType(type),
    mLastError(0),
    mPort(0),
    mSock(0)
{
  initializeOS();

  switch(mType)
  {
  case TYPE_UDP:
    mSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    break;
  case TYPE_TCP:
    mSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    break;
  default:
    break;
  }
}

Utilities::Socket::~Socket()
{
  close();
  finalizeOS();
}

int Utilities::Socket::getLastError()
{
  return mLastError;
}
