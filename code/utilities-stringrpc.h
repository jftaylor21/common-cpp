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
      MESSAGEID_DEREGISTER = 2,
      MESSAGEID_HEARTBEAT = 3
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

    struct Message
    {
      Message(MessageID msg, ClientID id=CLIENTID_SERVER, const ArgsList& args=ArgsList());

      MessageID msgID;
      ClientID clientID;
      ArgsList args;
    };

    typedef Callback1<Message> MessageCallback;

    template<typename Object>
    struct MessageObjectCallback : public ObjectCallback1<Object, Message>
    {
      MessageObjectCallback(Object* o, typename ObjectCallback1<Object, Message>::Function f) : ObjectCallback1<Object, Message>(o, f){}
    };

    StringRPC(bool server);
    ~StringRPC();

    bool initialize(const std::string& serverIP, unsigned int serverPort);
    bool send(MessageID type, ClientID id=CLIENTID_SERVER, const ArgsList& args=ArgsList());
    bool send(const Message& msg);
    void addCallback(MessageID type, const MessageCallback& callback);

    void onRegisterCallback(const Message& msg);
    void onAckRegisterCallback(const Message& msg);
    void onDeregisterCallback(const Message& msg);

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
