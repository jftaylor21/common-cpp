#include "utilities-time.h"

void Utilities::sleep(unsigned int ms)
{
  usleep(ms*1000);
}
