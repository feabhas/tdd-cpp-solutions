/** @file IDisplay.h
    \brief API for the IDisplay Interface.
*/
#ifndef _IDISPLAY_H
#define _IDISPLAY_H

namespace Display
{
  class IDisplay {
  public:
    virtual int display(const char* str) = 0;
    virtual ~IDisplay()                  = default;
  };
} // namespace

#endif // _IDISPLAY_H
