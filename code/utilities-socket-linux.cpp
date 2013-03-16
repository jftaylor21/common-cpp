#include "utilities-socket.h"

void Utilities::Socket::initializeOS()
{
}

void Utilities::Socket::finalizeOS()
{
}

bool Utilities::Socket::ipstr2int(const std::string &ipstr, unsigned long& ipint)
{
  return inet_pton(AF_INET, ipstr.c_str(), &ipint) == 1;
}
