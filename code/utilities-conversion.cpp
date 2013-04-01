#include "utilities-conversion.h"
#include <cstdlib>

int Utilities::toInt(const std::string &str)
{
  return atoi(str.c_str());
}
