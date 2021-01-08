/** @file display_stub.h
    \brief API for the abstracted Display_stub Display Module.
*/
#ifndef _Display_stub_H
#define _Display_stub_H

#include "IDisplay.h"

namespace Display
{
  class Display_stub : public IDisplay
  {
  public:
    Display_stub() = default;
    int display(const char *str) override;

    // private:
    //   unsigned count{};  // used for fake behaviour
  };

} // namespace Display

#endif // _Display_stub_H
