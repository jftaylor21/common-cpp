#include "utilities.h"
#include <cmath>
#include <cstdlib>

int Utilities::toInt(const std::string &str)
{
  return atoi(str.c_str());
}

int Utilities::clamp(int val, int min, int max, bool wrap)
{
  if (wrap)
  {
    int ret((val-min) % (max-min));
    ret = ret < 0 ? ret+max-min : ret;
    return ret+min;
  }
  else
  {
    return val < min ? min : (val > max ? max : val);
  }
}

double Utilities::clampf(double val, double min, double max, bool wrap)
{
  if (wrap)
  {
    double ret(fmod(val-min, max-min));
    ret = ret < 0 ? ret+max-min : ret;
    return ret+min;
  }
  else
  {
    return val < min ? min : (val > max ? max : val);
  }
}

double Utilities::interpolate(double val, double oldmin, double oldmax, double newmin, double newmax)
{
  return newmin + (val-oldmin) * (newmax-newmin) / (oldmax-oldmin);
}
