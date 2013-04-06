#ifndef UTILITIES_STRINGRPC_H
#define UTILITIES_STRINGRPC_H

#include <stdint.h>
#include <string>
#include <map>
#include "utilities-tokenizer.h"
#include "utilities-callback.h"
#include "utilities-socket.h"
#include "utilities-mutex.h"
#include "utilities-thread.h"

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
      CLIENTID_UNKNOWN = 0,
      CLIENTID_SERVER = 1,
      CLIENTID_BROADCAST = 2
    };

    typedef uint32_t MessageID;
    typedef uint32_t ClientID;
    typedef TokenList ArgsList;
    typedef Callback3<MessageID, ClientID, ArgsList> MessageCallback;

    template<typename Object>
    struct MessageObjectCallback : public ObjectCallback3<Object, MessageID, ClientID, ArgsList>
    {
      MessageObjectCallback(Object* o, typename ObjectCallback3<Object, MessageID, ClientID, ArgsList>::Function f) : ObjectCallback3<Object, MessageID, ClientID, ArgsList>(o, f){}
    };

    StringRPC(bool server);
    ~StringRPC();

    bool initialize(const std::string& serverIP, unsigned int serverPort);
    bool send(MessageID type, const ArgsList& args, ClientID id=CLIENTID_SERVER);
    void addCallback(MessageID type, const MessageCallback& callback);
    char forbiddenCharacter() const;

    void onRegisterCallback(const MessageID& msg, const ClientID& cl, const ArgsList& args);
    void onAckRegisterCallback(const MessageID& msg, const ClientID& id, const ArgsList& args);

  private:
    struct IPPort
    {
      IPPort() : port(0) {}
      IPPort(const std::string& ipin, unsigned int portin) : ip(ipin), port(portin) {}

      std::string ip;
      unsigned int port;
    };

    class ReceiveThread : public Thread
    {
    public:
      ReceiveThread(char delimiter);
      ~ReceiveThread();

      bool initialize(const std::string &ip, unsigned int port);
      void addCallback(MessageID type, const MessageCallback& callback);
      std::string ip() const;
      unsigned int port() const;

    protected:
      virtual void run();

    private:
      typedef std::map<MessageID, MessageCallback*> CallbackMap;

      const char mDelimiter;
      bool mInitialized;
      Socket mSock;
      Mutex mCallbackMutex;
      CallbackMap mCallbacks;
    };

    typedef std::map<ClientID, IPPort> IPPortMap;

    std::string serialize(MessageID type, const ArgsList& args);

    const char mDelimiter;
    bool mInitialized;
    ClientID mID;
    IPPortMap mNetwork;
    ReceiveThread mReceiveThread;
  };
}

#endif
