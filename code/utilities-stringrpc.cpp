#include "utilities-stringrpc.h"
#include "utilities-time.h"
#include "utilities-conversion.h"
#include <iostream>
#include <sstream>

Utilities::StringRPC::StringRPC(bool server)
  : mDelimiter(';'),
    mInitialized(false),
    mID(server?CLIENTID_SERVER:CLIENTID_UNKNOWN),
    mReceiveThread(mDelimiter)
{
}

Utilities::StringRPC::~StringRPC()
{
  mReceiveThread.join();
}

bool Utilities::StringRPC::initialize(const std::string &serverIP,
                                      unsigned int serverPort)
{
  if (!mInitialized)
  {
    if (mID == CLIENTID_UNKNOWN) //i am a client
    {
      if (mReceiveThread.initialize(INADDR_ANY, 0))
      {
        mReceiveThread.start();
        mInitialized = true;

        ArgsList args;
        std::string registerMsg(serialize(MESSAGEID_REGISTER, args));
        Socket sock(Socket::TYPE_UDP);
        if (sock.sendto(registerMsg.c_str(), registerMsg.length(), serverIP, serverPort))
        {
          IPPort server(serverIP, serverPort);
          mNetwork[CLIENTID_SERVER] = server;
        }
      }
    }
    else //i am a server
    {
      if (mReceiveThread.initialize(serverIP, serverPort))
      {
        mReceiveThread.addCallback(MESSAGEID_REGISTER, MessageObjectCallback<StringRPC>(this, &StringRPC::onRegisterCallback));
        mReceiveThread.start();
        mInitialized = true;
      }
    }
  }
  return mInitialized;
}

bool Utilities::StringRPC::send(MessageID type, const ArgsList &args, ClientID)
{
  bool ret(false);
  if (mInitialized)
  {
  }
  return ret;
}

void Utilities::StringRPC::addCallback(MessageID type, const MessageCallback& callback)
{
  mReceiveThread.addCallback(type, callback);
}

void Utilities::StringRPC::onRegisterCallback(const MessageID &msg,
                                              const ClientID &cl,
                                              const ArgsList &args)
{
}

char Utilities::StringRPC::forbiddenCharacter() const
{
  return mDelimiter;
}

std::string Utilities::StringRPC::serialize(MessageID type, const ArgsList &args)
{
  std::stringstream ss;
  ss << type << mDelimiter << mID;
  for(ArgsList::const_iterator it(args.begin()); it != args.end(); ++it)
  {
    ss << mDelimiter << *it;
  }
  return ss.str();
}

Utilities::StringRPC::ReceiveThread::ReceiveThread(char delimiter)
  : mDelimiter(delimiter),
    mInitialized(false),
    mSock(Socket::TYPE_UDP)
{
}

bool Utilities::StringRPC::ReceiveThread::initialize(const std::string &ip, unsigned int port)
{
  if (!mInitialized)
  {
    if (mSock.bind(ip, port))
    {
      mInitialized = true;
    }
  }
  return mInitialized;
}

bool Utilities::StringRPC::ReceiveThread::initialize(unsigned long ip, unsigned int port)
{
  if (!mInitialized)
  {
    if (mSock.bind(ip, port))
    {
      mInitialized = true;
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

void Utilities::StringRPC::ReceiveThread::run()
{
  while(mRunning)
  {
    char buf[4096];
    std::string ip;
    unsigned int port(0);
    if (mSock.recvfrom(buf, sizeof(buf), ip, port) > 0)
    {
      Utilities::TokenList t(Utilities::tokenize(buf, mDelimiter));
      if (t.size() > 1)
      {
        StringRPC::MessageID type(Utilities::toInt(t[0]));
        StringRPC::ClientID id(Utilities::toInt(t[1]));
        StringRPC::ArgsList args;
        if(t.size() > 2)
        {
          args = StringRPC::ArgsList(t.begin()+2, t.end());
        }

        if (type == StringRPC::MESSAGEID_REGISTER)
        {
          args.push_back(ip);
          args.push_back(Utilities::toString(port));
        }

        if (mCallbacks.count(type))
        {
          (*mCallbacks[type])(type, id, args);
        }
      }
    }
    Utilities::sleep(100);
  }
}
