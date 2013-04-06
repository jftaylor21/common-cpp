#ifndef UTILITIES_STRING_H
#define UTILITIES_STRING_H

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

  std::string replace(const std::string& input,
                      char oldValue,
                      const std::string& newValue);
}

#endif
