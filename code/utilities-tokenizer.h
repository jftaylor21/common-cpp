#ifndef UTILITIES_TOKENIZER_H
#define UTILITIES_TOKENIZER_H

#include <vector>
#include <string>

namespace Utilities
{
  typedef std::vector<std::string> TokenList;

  //two delimiters in a row escape the delimiter
  TokenList tokenize(const std::string& input, char delim, bool escape);
}

#endif
