#ifndef UTILITIES_SOCKET
#define UTILITIES_SOCKET

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#endif

namespace Utilities
{
  class Socket
  {
  public:
    enum SocketType
    {
      TYPE_UDP,
      TYPE_TCP
    };

    Socket(SocketType type);

  private:
    SocketType mType;

#ifdef WIN32
    SOCKET mSock;
#else
    int mSock;
#endif
  };
}

#endif
