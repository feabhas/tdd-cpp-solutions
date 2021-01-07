#include "lcd.h"
#include <cstring>

namespace Display
{
  int Lcd::display(const char* str)
  {
    static unsigned count = 1;
    switch (count) {
      case 1:
        // CHECK(string{ "Serial Number: 06:05:04:03:02:01" } == string{ str });
        break;
      case 2:
        // CHECK(string{ "85.00C" } == string{ str });
        break;
    }
    return strlen(str);
  }
}
