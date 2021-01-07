#ifndef LED_H
#define LED_H

class I_Led {
public:
  virtual void on()  = 0;
  virtual void off() = 0;
  virtual ~I_Led()   = default;
};

#endif // LED_H