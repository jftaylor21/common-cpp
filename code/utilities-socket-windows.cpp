#include "utilities-socket.h"
#include <iostream>

Utilities::Socket Utilities::Socket::accept()
{
  sockaddr_in sai;
  int saisize(sizeof(sai));
  Socket ret(mType);
  SOCKET accepted(::accept(mSock, reinterpret_cast<SOCKADDR*>(&sai), &saisize));
  updateLastError("Socket::accept: ");
  if (accepted != INVALID_SOCKET)
  {
    ret.mSock = accepted;
    ret.mIP = sai.sin_addr.s_addr;
    ret.mPort = ntohs(sai.sin_port);
  }
  return ret;
}

bool Utilities::Socket::close()
{
  bool ret(!closesocket(mSock));
  updateLastError("Socket::close: ");
  return ret;
}

bool Utilities::Socket::ipstr2int(const std::string &ipstr, unsigned long& ipint)
{
  long ret(inet_addr(ipstr.c_str()));
  ipint = ret;
  return ret != -1;
}

void Utilities::Socket::updateLastError(const std::string& prefix)
{
  mLastError = WSAGetLastError();
  if (mLastError)
  {
    printLastError(prefix);
  }
}

void Utilities::Socket::printLastError(const std::string &prefix)
{
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                0, getLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf, 0, 0);

  std::cout << prefix << (LPCTSTR)lpMsgBuf << std::endl;

  LocalFree(lpMsgBuf);
}

void Utilities::Socket::initializeOS()
{
  WSADATA info;
  WSAStartup(MAKEWORD(2, 2), &info);
}

void Utilities::Socket::finalizeOS()
{
  WSACleanup();
}
