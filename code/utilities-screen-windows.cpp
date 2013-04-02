#include "utilities-screen.h"
#include <Windows.h>
#include <conio.h>

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
