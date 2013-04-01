#ifndef UTILITIES_CONVERSION_H
#define UTILITIES_CONVERSION_H

#include <string>
#include <sstream>

namespace Utilities
{
  template<typename T>
  std::string toString(const T& t)
  {
    std::stringstream ss;
    ss <<  t;
    return ss.str();
  }

  int toInt(const std::string& str);
}

#endif
