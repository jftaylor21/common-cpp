#ifndef UTILITIES_SCREEN_H
#define UTILITIES_SCREEN_H

#include "utilities-callback.h"

namespace Utilities
{
  enum Color
  {
    COLOR_RESET,
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_GRAY,
    COLOR_YELLOW,
    COLOR_WHITE
  };

  void setTextColor(Color c);
  void echo(bool on);
  void clearscreen();
  void installSignalHandler(const Callback0& callback);
}

#endif
