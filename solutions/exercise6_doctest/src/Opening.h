#ifndef Opening_H
#define Opening_H

#include "StateMachine.h"

class Opening : public StateMachine {
public:
  Opening();
  ~Opening();
  StateMachine* button_pressed() override;
  StateMachine* fully_open() override;
  StateMachine* fully_closed() override;
  StateMachine* ir_beam_broken() override;
  StateMachine* motor_overcurrent() override;
};

#endif // Opening_H