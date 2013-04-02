#include "utilities-screen-linux.h"
#include "utilities-screen.h"

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
