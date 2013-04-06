#include "utilities-tokenizer.h"
#include <sstream>

Utilities::TokenList Utilities::tokenize(const std::string &input, char delim,
                                         bool escape)
{
  TokenList ret;
  std::string current;
  bool midescape(false);
  for(unsigned int i(0); i < input.size(); ++i)
  {
    if (input[i] == delim)
    {
      if (escape)
      {
        if (midescape)
        {
          current.push_back(delim);
          midescape = false;
        }
        else
        {
          midescape = true;
        }
      }
      else
      {
        if (!current.empty())
        {
          ret.push_back(current);
          current.clear();
        }
      }
    }
    else
    {
      if (midescape)
      {
        if (!current.empty())
        {
          ret.push_back(current);
          current.clear();
        }
        midescape = false;
      }
      current.push_back(input[i]);
    }
  }
  if (!current.empty())
  {
    ret.push_back(current);
  }
  return ret;
}
