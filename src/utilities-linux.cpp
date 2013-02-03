#include "utilities-linux.h"
#include "utilities.h"

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include <cstdio>
#include <iostream>

void Utilities::sleep(unsigned int ms)
{
  usleep(ms*1000);
}

bool Utilities::ttyMode(TTYMode mode)
{
  bool ret(false);

  termios t;
  tcgetattr(STDIN_FILENO, &t); //get attributes
  switch(mode)
  {
  case TTY_BUFFERED:
    ret = t.c_lflag & ICANON;
    break;
  case TTY_ECHO:
    ret = t.c_lflag & ECHO;
    break;
  default:
    std::cout << "Utilities::ttyMode: unknown mode" << mode << std::endl;
    break;
  }

  return ret;
}

void Utilities::setTTYMode(TTYMode mode, bool enabled)
{
  termios t;
  tcgetattr(STDIN_FILENO, &t); //get attributes
  switch(mode)
  {
  case TTY_BUFFERED:
    t.c_lflag = enabled ? (t.c_lflag | ICANON) : (t.c_lflag & ~ICANON);
    break;
  case TTY_ECHO:
    t.c_lflag = enabled ? (t.c_lflag | ECHO) : (t.c_lflag & ~ECHO);
    break;
  default:
    std::cout << "Utilities::setTTYMode: unknown mode" << mode << std::endl;
    break;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &t); //set attributes
}

int Utilities::bytesAvailable(unsigned int fd)
{
  int ret(0);
  if (ioctl(fd, FIONREAD, &ret))
  {
    ret = 0;
  }
  return ret;
}

char Utilities::getch(bool block)
{
  char ret(0);

  bool echo(ttyMode(TTY_ECHO));
  bool buffered(ttyMode(TTY_BUFFERED));

  if (buffered)
  {
    setTTYMode(TTY_BUFFERED, false);
  }
  if (echo)
  {
    setTTYMode(TTY_ECHO, false);
  }
  
  while(block && !bytesAvailable(STDIN_FILENO));
  
  if (read(STDIN_FILENO, &ret, 1) != 1)
  {
    ret = 0;
  }

  if (echo)
  {
    setTTYMode(TTY_ECHO, true);
  }
  if (buffered)
  {
    setTTYMode(TTY_BUFFERED, true);
  }

  return ret;
}

void Utilities::waitKey()
{
  while (!bytesAvailable(STDIN_FILENO))
  {
    sleep(50);
  }
}

//keycodes: http://ascii-table.com/ansi-escape-sequences-vt-100.php
Utilities::Key Utilities::getKey(bool block, bool clearBuffer)
{
  Key ret(KEY_NONE);

  bool echo(ttyMode(TTY_ECHO));
  bool buffered(ttyMode(TTY_BUFFERED));

  if (buffered)
  {
    setTTYMode(TTY_BUFFERED, false);
  }
  if (echo)
  {
    setTTYMode(TTY_ECHO, false);
  }

  if (block)
  {
    waitKey();
  }

  int bytesToRead(bytesAvailable(STDIN_FILENO));
  char buf(0);
  if (bytesToRead && read(STDIN_FILENO, &buf, 1) == 1)
  {
    --bytesToRead;
    ret = static_cast<Key>(buf);
    if (buf == KEY_ESC && bytesToRead
        && read(STDIN_FILENO, &buf, 1) == 1)
    {
      --bytesToRead;
      if (buf == KEY_LEFT_BRACKET && bytesToRead
          && read(STDIN_FILENO, &buf, 1) == 1)
      {
        if (buf == KEY_A)
        {
          ret = KEY_UP;
        }
        else if (buf == KEY_B)
        {
          ret = KEY_DOWN;
        }
        else if (buf == KEY_C)
        {
          ret = KEY_RIGHT;
        }
        else if (buf == KEY_D)
        {
          ret = KEY_LEFT;
        }
      }
    }
  }

  if (clearBuffer)
  {
    read(STDIN_FILENO, &buf, bytesAvailable(STDIN_FILENO));
  }

  if (echo)
  {
    setTTYMode(TTY_ECHO, true);
  }
  if (buffered)
  {
    setTTYMode(TTY_BUFFERED, true);
  }

  return ret;
}

bool Utilities::getKey(Key k)
{
  bool ret(false);

  std::cout << "Utilities::getKey: not implemented in linux" << std::endl;

  return ret;
}

void Utilities::echo(bool on)
{
  setTTYMode(TTY_ECHO, on);
}
