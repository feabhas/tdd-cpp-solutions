/** @file lcd.h
    \brief API for the abstracted LCD Display Module.
*/
#ifndef _LCD_H
#define _LCD_H

#include "IDisplay.h"

namespace Display
{
  class Lcd : public IDisplay {
  public:
    Lcd()  = default;
    ~Lcd() = default;
    int display(const char* str) override;
  };

} // namespace

#endif // _LCD_H
