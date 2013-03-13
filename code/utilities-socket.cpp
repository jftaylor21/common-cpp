#include "utilities-socket.h"

Utilities::Socket::Socket(SocketType type)
  : mType(type),
    mSock(0)
{
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
