#include "utilities-time.h"
#include <ctime>

std::string Utilities::timeString()
{
  time_t rawtime(time(0));
  tm* timeinfo(localtime(&rawtime));
  char buf[9]; //HH:MM:SS
  strftime(buf, sizeof(buf), "%T", timeinfo);
  return buf;
}
