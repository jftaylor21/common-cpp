#include "utilities-stringrpc.h"
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

void Utilities::StringRPC::addCallback(MessageID type, MessageCallback callback)
{
  mReceiveThread.addCallback(type, callback);
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

void Utilities::StringRPC::ReceiveThread::addCallback(MessageID type, MessageCallback callback)
{
  mCallbackMutex.lock();
  if (mCallbacks.count(type))
  {
    std::cout << "Utilities::StringRPC::ReceiveThread::addCallback: message type " << type << " already has a callback"
              << std::endl;
  }
  else
  {
    mCallbacks.insert(std::pair<MessageID, MessageCallback>(type, callback));
  }
  mCallbackMutex.unlock();
}

void Utilities::StringRPC::ReceiveThread::run()
{
}
