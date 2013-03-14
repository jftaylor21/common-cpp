#include "utilities-socket.h"

bool Utilities::Socket::validateIP(const std::string &ip)
{
  std::wstring wip(ip.begin(), ip.end());
  sockaddr_in sai;
  memset(&sai, 0, sizeof(sai));
  sai.sin_family = AF_INET;
  SOCKADDR sa(static_cast<SOCKADDR>(sa));
  int sasize(sizeof(sa));

  return WSAStringToAddress(const_cast<WCHAR*>(wip.c_str()), AF_INET, 0, &sa, &sasize) != 0;
}
