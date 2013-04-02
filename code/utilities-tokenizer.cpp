#include "utilities-tokenizer.h"
#include <sstream>

Utilities::TokenList Utilities::tokenize(const std::string &input, char delim)
{
  TokenList ret;
  std::stringstream ss(input);
  std::string out;
  while (std::getline(ss, out, delim))
  {
    ret.push_back(out);
  }
  return ret;
}
