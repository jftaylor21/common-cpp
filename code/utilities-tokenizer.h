#ifndef UTILITIES_TOKENIZER_H
#define UTILITIES_TOKENIZER_H

#include <vector>
#include <string>

namespace Utilities
{
  typedef std::vector<std::string> TokenList;

  TokenList tokenize(const std::string& input, char delim);
}

#endif
