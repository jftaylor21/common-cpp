#ifndef UTILITIES_H
#define UTILITIES_H

#include "utilities-enums.h"

#ifdef WIN32
  #include "utilities-windows.h"
#else
  #include "utilities-linux.h"
#endif

#include <string>
#include <sstream>
#include <cmath>

#ifndef DLL_EXPORT
#define DLL_EXPORT
#endif

#ifndef DLL_IMPORT
#define DLL_IMPORT
#endif

#ifdef UTILITIES_EXPORT
  #define UTILITIES_LIB DLL_EXPORT
#else
  #define UTILITIES_LIB DLL_IMPORT
#endif


namespace Utilities
{
  //type conversions
  template<typename T>
  std::string toString(const T& t)
  {
    std::stringstream ss;
    ss <<  t;
    return ss.str();
  }

  int toInt(const std::string& str);

  //math
  const double PI(4*std::atan(1));

  int clamp(int val, int min, int max, bool wrap=false);
  double clampf(double val, double min, double max, bool wrap=false);

  double interpolate(double val, double oldmin, double oldmax, double newmin, double newmax);

  //os independent
  void sleep(unsigned int ms);

  void waitKey();
  Key getKey(bool block = false, bool clearBuffer = false);
  bool getKey(Key k);

  void echo(bool on);
}

#endif
