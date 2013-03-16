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

bool Utilities::Socket::bind(const std::string &ip, unsigned int port)
{
  bool ret(false);
  sockaddr_in sai;
  ret = ipstr2int(ip, sai.sin_addr.s_addr);
  updateLastError("Socket::bind: ");
  if (ret)
  {
    sai.sin_port = htons(port);
    sai.sin_family = AF_INET;
    int saisize(sizeof(sai));
    ret = ::bind(mSock, reinterpret_cast<sockaddr*>(&sai), saisize) == 0;
    updateLastError("Socket::bind: ");
    if (ret)
    {
      mIP = ip;
      mPort = port;
    }
  }
  return ret;
}

bool Utilities::Socket::connect(const std::string &ip, unsigned int port)
{
  bool ret(false);
  sockaddr_in sai;
  memset(&sai, 0, sizeof(sockaddr_in));
  ret = ipstr2int(ip, sai.sin_addr.s_addr);
  updateLastError("Socket::connect: ");
  if (ret)
  {
    sai.sin_family = AF_INET;
    sai.sin_port = htons(port);
    int saisize(sizeof(sai));
    ret = ::connect(mSock, reinterpret_cast<sockaddr*>(&sai), saisize) == 0;
    updateLastError("Socket::connect: ");
  }
  return ret;
}

bool Utilities::Socket::listen(unsigned int backlog)
{
  bool ret(::listen(mSock, backlog) == 0);
  updateLastError("Socket::listen: ");
  return ret;
}

unsigned int Utilities::Socket::recv(char *buf, unsigned int bytes)
{
  unsigned int ret(0);
  ret = ::recv(mSock, buf, bytes, 0);
  updateLastError("Socket::recv: ");
  return ret;
}

bool Utilities::Socket::validateIP(const std::string &ip)
{
  unsigned long test;
  return ipstr2int(ip, test);
}

int Utilities::Socket::getLastError()
{
  return mLastError;
}
