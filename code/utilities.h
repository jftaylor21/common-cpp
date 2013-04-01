#ifndef UTILITIES_H
#define UTILITIES_H

#include "utilities-enums.h"
#include "utilities-importexport.h"

#ifdef WIN32
  #include "utilities-windows.h"
#else
  #include "utilities-linux.h"
#endif


namespace Utilities
{
  void sleep(unsigned int ms);

  void waitKey();
  Key getKey(bool block = false, bool clearBuffer = false);
  bool getKey(Key k);

  void echo(bool on);
  void clearscreen();
}

#endif
