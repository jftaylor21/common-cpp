#include "utilities-socket.h"

bool Utilities::Socket::validateIP(const std::string &ip)
{
  sockaddr_in sa;
  return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 0;
}
