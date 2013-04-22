#include "utilities-keyboard.h"
#include "utilities-logger.h"

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

  Utilities::Logger::get().error("Utilities::getKey: not implemented in linux\n");

  return ret;
}
