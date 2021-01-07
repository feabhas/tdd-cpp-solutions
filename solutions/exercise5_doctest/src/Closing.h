#ifndef Closing_H
#define Closing_H

#include "StateMachine.h"

class Closing : public StateMachine {
public:
  Closing();
  ~Closing();
  StateMachine* button_pressed() override;
  StateMachine* fully_open() override;
  StateMachine* fully_closed() override;
  StateMachine* ir_beam_broken() override;
  StateMachine* motor_overcurrent() override;
};

#endif // Closing_H