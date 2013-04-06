#include "utilities-tokenizer.h"
#include <sstream>

Utilities::TokenList Utilities::tokenize(const std::string &input, char delim,
                                         bool escape)
{
  TokenList ret;
  std::stringstream ss(input);
  char delimstr[2] = {delim, '\0'};
  std::string outprev;
  std::string out;
  bool midescape(false);
  while (std::getline(ss, out, delim))
  {
    if (escape && out.empty() && !outprev.empty())
    {
      midescape = true;
    }
    else if (!outprev.empty())
    {
      if (midescape)
      {
        outprev += delimstr+out;
        midescape = false;
      }
      else
      {
        ret.push_back(outprev);
        outprev = out;
      }
    }
    else
    {
      outprev = out;
    }
  }
  if (!outprev.empty())
  {
    ret.push_back(outprev);
  }

  return ret;
}
