#include "utilities-string.h"
#include <cstdlib>

int Utilities::toInt(const std::string &str)
{
  return atoi(str.c_str());
}

std::string Utilities::replace(const std::string &input,
                               char oldValue,
                               const std::string &newValue)
{
  std::string ret;
  for(unsigned int i(0); i < input.size(); ++i)
  {
    if (input[i] == oldValue)
    {
      ret += newValue;
    }
    else
    {
      ret.push_back(input[i]);
    }
  }
  return ret;
}
