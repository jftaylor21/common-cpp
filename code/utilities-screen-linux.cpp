#include "utilities-screen-linux.h"
#include "utilities-screen.h"
#include "utilities-logger.h"
#include <iostream>

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
    Logger::get().error("Utilities::ttyMode: unknown mode %d\n", mode);
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
    Logger::get().error("Utilities::setTTYMode: unknown mode %d\n", mode);
    break;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &t); //set attributes
}

void Utilities::setTextColor(Color c)
{
  int color(0);
  switch(c)
  {
  case COLOR_RESET:
    color = 0;
    break;
  case COLOR_BLACK:
    color = 30;
    break;
  case COLOR_BLUE:
    color = 34;
    break;
  case COLOR_GREEN:
    color = 32;
    break;
  case COLOR_CYAN:
    color = 36;
    break;
  case COLOR_RED:
    color = 31;
    break;
  case COLOR_MAGENTA:
    color = 35;
    break;
  case COLOR_GRAY:
    color = 37;
    break;
  case COLOR_YELLOW:
    color = 33;
    break;
  case COLOR_WHITE:
    color = 37;
    break;
  }
  std::cout << "\033]" << color << (c==COLOR_GRAY?";2":"") << "m";
}

void Utilities::echo(bool on)
{
  setTTYMode(TTY_ECHO, on);
}

void Utilities::clearscreen()
{
  if (!cur_term)
  {
    int result(0);
    setupterm(0, STDOUT_FILENO, &result);
    if (result <= 0)
    {
      putp(tigetstr("clear"));
    }
  }
}
