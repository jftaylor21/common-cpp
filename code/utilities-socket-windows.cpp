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

bool Utilities::Socket::ipint2str(unsigned long ipint, std::string &ipstr)
{
  bool ret(false);
  in_addr ina;
  ina.s_addr = ipint;
  char* temp(inet_ntoa(ina));
  if (temp)
  {
    ipstr = std::string(temp);
    ret = true;
  }
  return ret;
}

bool Utilities::Socket::localIP(std::string &ip)
{
  bool ret(false);
  char buf[80];
  if(gethostname(buf, sizeof(buf)) != SOCKET_ERROR)
  {
    hostent* phe(gethostbyname(buf));
    if (phe && phe->h_addr_list[0])
    {
      in_addr addr;
      memcpy(&addr, phe->h_addr_list[0], sizeof(addr));
      ret = ipint2str(addr.s_addr, ip);
    }
  }
  return ret;
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
  wchar_t* lpMsgBuf(0);
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                0, getLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf, 0, 0);

  if (lpMsgBuf)
  {
    std::cout << prefix;
    std::wcout << lpMsgBuf << std::endl;
    LocalFree(lpMsgBuf);
  }
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
