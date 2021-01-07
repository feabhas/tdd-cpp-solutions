#ifndef Closed_H
#define Closed_H

#include "StateMachine.h"

class Closed : public StateMachine {
public:
  Closed();
  ~Closed();
  StateMachine* button_pressed() override;
  StateMachine* fully_open() override;
  StateMachine* fully_closed() override;
  StateMachine* ir_beam_broken() override;
  StateMachine* motor_overcurrent() override;
};

#endif // Closed_H