#include "utilities-stringrpc.h"
#include <iostream>

Utilities::StringRPC::StringRPC(bool server)
  : mInitialized(false),
    mID(server?CLIENTID_SERVER:CLIENTID_UNKNOWN),
    mSock(Socket::TYPE_UDP)
{
}

Utilities::StringRPC::~StringRPC()
{
  mSock.close();
}

bool Utilities::StringRPC::initialize(const std::string &serverIP,
                                      unsigned int serverPort)
{
  if (!mInitialized)
  {
    if (mID) //i am a client
    {
    }
    else //i am a server
    {
      if (mSock.bind(serverIP, serverPort))
      {
        mInitialized = true;
      }
    }
  }
  return mInitialized;
}

bool Utilities::StringRPC::send(MessageID type, const ArgsList &args, ClientID)
{
  bool ret(false);
  return ret;
}

void Utilities::StringRPC::addCallback(MessageID type, MessageCallback callback)
{
  if (mCallbacks.count(type))
  {
    std::cout << "Utilities::StringRPC::addCallback: message type " << type << " already has a callback"
              << std::endl;
  }
  else
  {
    mCallbacks.insert(std::pair<MessageID, MessageCallback>(type, callback));
  }
}
