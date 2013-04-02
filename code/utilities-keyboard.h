#ifndef UTILITIES_KEYBOARD_H
#define UTILITIES_KEYBOARD_H

#include "utilities-enums.h"

namespace Utilities
{
  void waitKey();
  Key getKey(bool block = false, bool clearBuffer = false);
  bool getKey(Key k);
}
#endif
