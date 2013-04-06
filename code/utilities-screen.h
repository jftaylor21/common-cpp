#ifndef UTILITIES_SCREEN_H
#define UTILITIES_SCREEN_H

#include "utilities-callback.h"

namespace Utilities
{
  void echo(bool on);
  void clearscreen();
  void installSignalHandler(const Callback0& callback);
}

#endif
