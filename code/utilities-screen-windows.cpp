#include "utilities-screen.h"
#include <Windows.h>
#include <conio.h>

void Utilities::setTextColor(Color c)
{
  HANDLE stdhandle(GetStdHandle(STD_OUTPUT_HANDLE));
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(stdhandle, &csbi);
  static WORD oldcolor(csbi.wAttributes);

  WORD color(oldcolor);
  switch(c)
  {
  case COLOR_RESET:
    break;
  case COLOR_BLACK:
    color = 0;
    break;
  case COLOR_BLUE:
    color = 1;
    break;
  case COLOR_GREEN:
    color = 2;
    break;
  case COLOR_CYAN:
    color = 3;
    break;
  case COLOR_RED:
    color = 4;
    break;
  case COLOR_MAGENTA:
    color = 5;
    break;
  case COLOR_GRAY:
    color = 7;
    break;
  case COLOR_YELLOW:
    color = 14;
    break;
  case COLOR_WHITE:
    color = 15;
    break;
  }
  SetConsoleTextAttribute(stdhandle, color);
}

void Utilities::echo(bool on)
{
}

void Utilities::clearscreen()
{
  HANDLE hstdout(GetStdHandle(STD_OUTPUT_HANDLE));
  if (hstdout != INVALID_HANDLE_VALUE)
  {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hstdout, &csbi))
    {
      DWORD cellCount(csbi.dwSize.X*csbi.dwSize.Y);
      DWORD count(0);
      COORD homeCoord = {0,0};
      if (FillConsoleOutputCharacter(hstdout, ' ', cellCount, homeCoord, &count))
      {
        if (FillConsoleOutputAttribute(hstdout, csbi.wAttributes, cellCount, homeCoord, &count))
        {
          SetConsoleCursorPosition(hstdout, homeCoord);
        }
      }
    }
  }
}
