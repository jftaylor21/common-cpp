#ifndef UTILITIES_STRINGRPC_H
#define UTILITIES_STRINGRPC_H

#include <stdint.h>
#include <string>
#include <map>
#include "utilities-tokenizer.h"
#include "utilities-callback.h"

namespace Utilities
{
  class StringRPC
  {
  public:
    typedef uint32_t MessageID;
    typedef uint32_t ClientID;
    typedef Callback3<MessageID, ClientID, TokenList> MessageCallback;

    StringRPC(bool server);
    ~StringRPC();

    bool initialize(const std::string& ip, unsigned int port);
    bool send(MessageID type, const TokenList& args, ClientID=0);
    void addCallback(MessageID type, MessageCallback callback);

  private:
    typedef std::map<MessageID, MessageCallback> CallbackMap;

    struct Message
    {
      void encode(MessageID type, ClientID src, const TokenList& args);
      void decode(MessageID& type, ClientID& src, TokenList& args);

      std::string mRawData;
    };

    ClientID mID;
    std::string mIP;
    unsigned int mPort;
    CallbackMap mCallbacks;
  };
}

#endif
