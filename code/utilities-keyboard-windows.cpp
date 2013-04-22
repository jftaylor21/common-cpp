#include "utilities-keyboard.h"
#include "utilities-time.h"
#include "utilities-logger.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <climits>

void Utilities::waitKey()
{
  while (!_kbhit())
  {
    sleep(50);
  }
}

//keycodes: http://msdn.microsoft.com/en-us/library/aa299374(VS.60).aspx
Utilities::Key Utilities::getKey(bool block, bool clearBuffer)
{
  Key ret(KEY_NONE);

  if (block)
  {
    waitKey();
  }

  if (_kbhit())
  {
    ret = static_cast<Key>(_getch());
    if (ret == 0 || ret == 0xe0)
    {
      ret = static_cast<Key>(_getch());
      switch(ret)
      {
      case 72:
        ret = KEY_UP;
        break;
      case 75:
        ret = KEY_LEFT;
        break;
      case 77:
        ret = KEY_RIGHT;
        break;
      case 80:
        ret = KEY_DOWN;
        break;
      default:
        Logger::get().error("Utilities::getKey: I don't understand: %d\n", ret);
        ret = KEY_NONE;
      }
    }
  }

  return ret;
}

bool Utilities::getKey(Key k)
{
  bool ret(false);
  int vk(0);
  if (KEY_A <= k && k <= KEY_Z)
  {
    if (!(GetAsyncKeyState(VK_SHIFT)&SHRT_MAX))
    {
      return false;
    }
  }
  switch(k)
  {
  case KEY_ENTER:
    vk = VK_RETURN;
    break;
  case KEY_SPACE:
    vk = VK_SPACE;
    break;
  case KEY_A:
  case KEY_a:
    vk = 'A';
    break;
  case KEY_B:
  case KEY_b:
    vk = 'B';
    break;
  case KEY_C:
  case KEY_c:
    vk = 'C';
    break;
  case KEY_D:
  case KEY_d:
    vk = 'D';
    break;
  case KEY_E:
  case KEY_e:
    vk = 'E';
    break;
  case KEY_F:
  case KEY_f:
    vk = 'F';
    break;
  case KEY_G:
  case KEY_g:
    vk = 'G';
    break;
  case KEY_H:
  case KEY_h:
    vk = 'H';
    break;
  case KEY_I:
  case KEY_i:
    vk = 'I';
    break;
  case KEY_J:
  case KEY_j:
    vk = 'J';
    break;
  case KEY_K:
  case KEY_k:
    vk = 'K';
    break;
  case KEY_L:
  case KEY_l:
    vk = 'L';
    break;
  case KEY_M:
  case KEY_m:
    vk = 'M';
    break;
  case KEY_N:
  case KEY_n:
    vk = 'N';
    break;
  case KEY_O:
  case KEY_o:
    vk = 'O';
    break;
  case KEY_P:
  case KEY_p:
    vk = 'P';
    break;
  case KEY_Q:
  case KEY_q:
    vk = 'Q';
    break;
  case KEY_R:
  case KEY_r:
    vk = 'R';
    break;
  case KEY_S:
  case KEY_s:
    vk = 'S';
    break;
  case KEY_T:
  case KEY_t:
    vk = 'T';
    break;
  case KEY_U:
  case KEY_u:
    vk = 'U';
    break;
  case KEY_V:
  case KEY_v:
    vk = 'V';
    break;
  case KEY_W:
  case KEY_w:
    vk = 'W';
    break;
  case KEY_X:
  case KEY_x:
    vk = 'X';
    break;
  case KEY_Y:
  case KEY_y:
    vk = 'Y';
    break;
  case KEY_Z:
  case KEY_z:
    vk = 'Z';
    break;
  case KEY_LEFT_BRACKET:
    vk = VK_OEM_4;
    break;
  case KEY_RIGHT_BRACKET:
    vk = VK_OEM_6;
    break;
  case KEY_ESC:
    vk = VK_ESCAPE;
    break;
  case KEY_UP:
    vk = VK_UP;
    break;
  case KEY_DOWN:
    vk = VK_DOWN;
    break;
  case KEY_LEFT:
    vk = VK_LEFT;
    break;
  case KEY_RIGHT:
    vk = VK_RIGHT;
    break;
  default:
    Logger::get().error("Utilities::getKey: I don't understand: %d\n", k);
  }

  ret = GetAsyncKeyState(vk) & SHRT_MAX;

  return ret;
}
