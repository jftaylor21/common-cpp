#include "utilities-file.h"
#include <sys/ioctl.h>

int Utilities::bytesAvailable(unsigned int fd)
{
  int ret(0);
  if (ioctl(fd, FIONREAD, &ret))
  {
    ret = 0;
  }
  return ret;
}
