#ifndef UTILITIES_SOCKET
#define UTILITIES_SOCKET

#include <string>

#ifdef WIN32
#include <winsock2.h>
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
    ~Socket();

    Socket accept();
    bool bind(const std::string& ip, unsigned int port);
    bool close();
    bool connect(const std::string& ip, unsigned int port);
    bool listen(unsigned int backlog);
    unsigned int recv(char* buf, unsigned int bytes);
    unsigned int recvfrom(char *buf, unsigned int bytes, std::string& ip, unsigned int& port);
    unsigned int send(char* buf, unsigned int bytes);
    unsigned int sendto(char* buf, unsigned int bytes, const std::string& ip, unsigned int port);
    int getLastError();

    static bool validateIP(const std::string& ip);
    static std::string hostIP();

  private:
    void updateLastError(const std::string& prefix="");
    void printLastError(const std::string& prefix="");
    static bool ipstr2int(const std::string& ipstr, unsigned long& ipint);
    static bool ipint2str(unsigned long ipint, std::string& ipstr);

    static void initializeOS();
    static void finalizeOS();

    SocketType mType;
    int mLastError;
    std::string mIP;
    unsigned int mPort;

#ifdef WIN32
    SOCKET mSock;
#else
    int mSock;
#endif
  };
}

#endif
