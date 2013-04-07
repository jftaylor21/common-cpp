#include "utilities-stringrpc.h"
#include "utilities-time.h"
#include "utilities-string.h"
#include <iostream>
#include <sstream>

Utilities::StringRPC::Message::Message(MessageID msg, ClientID id, const ArgsList &args)
  : msgID(msg),
    clientID(id),
    args(args)
{
}

Utilities::StringRPC::StringRPC(bool server)
  : mDelimiter(';'),
    mInitialized(false),
    mID(server?CLIENTID_SERVER:CLIENTID_UNKNOWN),
    mReceiveThread(mDelimiter)
{
}

Utilities::StringRPC::~StringRPC()
{
  if (mID != CLIENTID_SERVER)
  {
    send(Utilities::StringRPC::MESSAGEID_DEREGISTER, CLIENTID_SERVER);
  }
  mReceiveThread.join();
}

bool Utilities::StringRPC::initialize(const std::string &serverIP,
                                      unsigned int serverPort)
{
  if (!mInitialized)
  {
    if (mID == CLIENTID_UNKNOWN) //i am a client
    {
      std::string localip;
      Utilities::Socket::localIP(localip);
      if (mReceiveThread.initialize(localip, 0))
      {
        mReceiveThread.addCallback(MESSAGEID_ACKREGISTER, MessageObjectCallback<StringRPC>(this, &StringRPC::onAckRegisterCallback));
        mReceiveThread.start();
        mNetwork[CLIENTID_SERVER] = IPPort(serverIP, serverPort);
        mInitialized = true;

        ArgsList args;
        args.push_back(mReceiveThread.ip());
        args.push_back(Utilities::toString(mReceiveThread.port()));
        while(mID == CLIENTID_UNKNOWN)
        {
          send(MESSAGEID_REGISTER, CLIENTID_SERVER, args);
          Utilities::sleep(100);
        }
      }
    }
    else //i am a server
    {
      if (mReceiveThread.initialize(serverIP, serverPort))
      {
        mReceiveThread.addCallback(MESSAGEID_REGISTER, MessageObjectCallback<StringRPC>(this, &StringRPC::onRegisterCallback));
        mReceiveThread.addCallback(MESSAGEID_DEREGISTER, MessageObjectCallback<StringRPC>(this, &StringRPC::onDeregisterCallback));
        mReceiveThread.start();
        mInitialized = true;
      }
    }
  }
  return mInitialized;
}

bool Utilities::StringRPC::send(MessageID type, ClientID id, const ArgsList &args)
{
  bool ret(false);
  if (id == CLIENTID_BROADCAST)
  {
    IPPortMap::const_iterator it(mNetwork.begin());
    for(; it != mNetwork.end(); ++it)
    {
      if (it->first != mID)
      {
        send(type, it->first, args);
      }
    }
  }
  else if (mInitialized &&
           mNetwork.count(id) &&
           (mID != CLIENTID_UNKNOWN || type == MESSAGEID_REGISTER))
  {
    std::string data(serialize(type, args));
    Socket sock(Socket::TYPE_UDP);
    sock.sendto(data.c_str(), data.size()+1, mNetwork[id].ip, mNetwork[id].port);
  }
  else
  {
    std::cout << "StringRPC: Cannot send message due to conditions not met"
              << std::endl;
  }
  return ret;
}

void Utilities::StringRPC::addCallback(MessageID type, const MessageCallback& callback)
{
  mReceiveThread.addCallback(type, callback);
}

void Utilities::StringRPC::onRegisterCallback(const Message& msg)
{
  if (msg.args.size() == 2)
  {
    std::string ip(msg.args[0]);
    unsigned int port(Utilities::toInt(msg.args[1]));
    ClientID id(mNetwork.size()+CLIENTID_BROADCAST+1);
    while (mNetwork.count(id)) //keep searching for an unused id
    {
      ++id;
    }
    mNetwork[id] = IPPort(ip, port);
    std::cout << "Registered client: " << id << " from "
              << ip << ":" << port << std::endl;

    ArgsList alist;
    alist.push_back(Utilities::toString(id));
    send(MESSAGEID_ACKREGISTER, id, alist);
  }
}

void Utilities::StringRPC::onAckRegisterCallback(const Message& msg)
{
  if (msg.args.size() == 1)
  {
    mID = Utilities::toInt(msg.args[0]);
  }
}

void Utilities::StringRPC::onDeregisterCallback(const Message &msg)
{
  mNetwork.erase(msg.clientID);
  std::cout << "Deregistered client: " << msg.clientID << std::endl;
}

std::string Utilities::StringRPC::serialize(MessageID type, const ArgsList &args)
{
  const char ddelim[3] = {mDelimiter, mDelimiter, '\0'};
  std::stringstream ss;
  ss << type << mDelimiter << mID;
  for(ArgsList::const_iterator it(args.begin()); it != args.end(); ++it)
  {
    ss << mDelimiter << Utilities::replace(*it, mDelimiter, ddelim);
  }
  return ss.str();
}

Utilities::StringRPC::ReceiveThread::ReceiveThread(char delimiter)
  : mDelimiter(delimiter),
    mInitialized(false),
    mSock(Socket::TYPE_UDP)
{
}

Utilities::StringRPC::ReceiveThread::~ReceiveThread()
{
  for (CallbackMap::iterator it(mCallbacks.begin()); it != mCallbacks.end(); ++it)
  {
    delete it->second;
    it->second = 0;
  }
}

bool Utilities::StringRPC::ReceiveThread::initialize(const std::string &ip, unsigned int port)
{
  if (!mInitialized)
  {
    if (mSock.bind(ip, port))
    {
      mInitialized = true;
      mSock.setBlocking(false);
    }
  }
  return mInitialized;
}

void Utilities::StringRPC::ReceiveThread::addCallback(MessageID type, const MessageCallback& callback)
{
  mCallbackMutex.lock();
  if (mCallbacks.count(type))
  {
    std::cout << "Utilities::StringRPC::ReceiveThread::addCallback: message type " << type << " already has a callback"
              << std::endl;
  }
  else
  {
    mCallbacks.insert(std::pair<MessageID, MessageCallback*>(type, callback.clone()));
  }
  mCallbackMutex.unlock();
}

std::string Utilities::StringRPC::ReceiveThread::ip() const
{
  return mSock.ip();
}

unsigned int Utilities::StringRPC::ReceiveThread::port() const
{
  return mSock.port();
}

void Utilities::StringRPC::ReceiveThread::run()
{
  while(mRunning)
  {
    char buf[4096];
    std::string ip;
    unsigned int port(0);
    if (mSock.recvfrom(buf, sizeof(buf), ip, port) > 0)
    {
      Utilities::TokenList t(Utilities::tokenize(buf, mDelimiter, true));
      if (t.size() > 1)
      {
        StringRPC::MessageID type(Utilities::toInt(t[0]));
        StringRPC::ClientID id(Utilities::toInt(t[1]));
        StringRPC::ArgsList args;
        if(t.size() > 2)
        {
          args = StringRPC::ArgsList(t.begin()+2, t.end());
        }
        StringRPC::Message msg(type, id, args);

        if (mCallbacks.count(type))
        {
          (*mCallbacks[type])(msg);
        }
        else
        {
          std::cout << "No callbacks registered for message: "
                    << type << " from " << id
                    << std::endl;
        }
      }
    }
    else
    {
      Utilities::sleep(100);
    }
  }
}
