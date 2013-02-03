#ifndef UTILITIES_LINUX_H
#define UTILITIES_LINUX_H

namespace Utilities
{
  enum TTYMode
  {
    TTY_BUFFERED,
    TTY_ECHO
  };

  bool ttyMode(TTYMode mode);
  void setTTYMode(TTYMode mode, bool enabled);

  int bytesAvailable(unsigned int fd);

  char getch(bool block);
}

#endif
