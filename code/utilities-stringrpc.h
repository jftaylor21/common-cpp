#ifndef UTILITIES_STRINGRPC_H
#define UTILITIES_STRINGRPC_H

#include <stdint.h>
#include <string>
#include <map>
#include "utilities-tokenizer.h"
#include "utilities-callback.h"
#include "utilities-socket.h"

namespace Utilities
{
  class StringRPC
  {
  public:
    enum ReservedMessageID
    {
      MESSAGEID_REGISTER = 0,
      MESSAGEID_ACKREGISTER = 1,
      MESSAGEID_DEREGISTER = 2
    };

    enum ReservedClientID
    {
      CLIENTID_SERVER = 0,
      CLIENTID_UNKNOWN = -1
    };

    typedef uint32_t MessageID;
    typedef uint32_t ClientID;
    typedef TokenList ArgsList;
    typedef Callback3<MessageID, ClientID, ArgsList> MessageCallback;

    StringRPC(bool server);
    ~StringRPC();

    bool initialize(const std::string& serverIP, unsigned int serverPort);
    bool send(MessageID type, const ArgsList& args, ClientID=0);
    void addCallback(MessageID type, MessageCallback callback);
    char forbiddenCharacter() const;

  private:
    struct IPPort
    {
      IPPort() : port(0) {}
      IPPort(const std::string& ipin, unsigned int portin) : ip(ipin), port(portin) {}

      std::string ip;
      unsigned int port;
    };

    typedef std::map<MessageID, MessageCallback> CallbackMap;
    typedef std::map<ClientID, IPPort> IPPortMap;

    std::string serialize(MessageID type, const ArgsList& args);

    const char mDeliminator;
    bool mInitialized;
    ClientID mID;
    CallbackMap mCallbacks;
    Socket mSock;
    IPPortMap mNetwork;
  };
}

#endif
