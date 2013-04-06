#include "utilities-screen.h"
#include <csignal>

namespace Utilities
{
  void exitCallback(int s);

  Callback0 gExitCallback(Utilities::nop);
}

void Utilities::exitCallback(int /*s*/)
{
  gExitCallback();
}

void Utilities::installSignalHandler(const Callback0 &callback)
{
  gExitCallback = callback;
  signal(SIGINT, Utilities::exitCallback);
  signal(SIGTERM, Utilities::exitCallback);
  signal(SIGABRT, Utilities::exitCallback);
}
