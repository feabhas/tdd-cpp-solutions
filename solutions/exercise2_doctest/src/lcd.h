/** @file lcd.h 
    \brief API for the abstracted LCD Display Module.
*/
#ifndef _LCD_H
#define _LCD_H

namespace Display {
    
class Lcd {
public:
  Lcd() = default;
  ~Lcd() = default;
  int display(const char* str);
private:
};

} // namespace

#endif // _LCD_H
