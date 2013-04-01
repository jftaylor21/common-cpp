#ifndef UTILITIES_MATH_H
#define UTILITIES_MATH_H

#include <cmath>

namespace Utilities
{
  const double PI(4*std::atan(1));

  int clamp(int val, int min, int max, bool wrap=false);
  double clampf(double val, double min, double max, bool wrap=false);

  double interpolate(double val, double oldmin, double oldmax, double newmin, double newmax);
}

#endif
