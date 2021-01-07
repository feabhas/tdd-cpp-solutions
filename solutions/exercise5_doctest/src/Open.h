#ifndef Open_H
#define Open_H

#include "StateMachine.h"

class Open : public StateMachine {
public:
  Open();
  ~Open();
  StateMachine* button_pressed() override;
  StateMachine* fully_open() override;
  StateMachine* fully_closed() override;
  StateMachine* ir_beam_broken() override;
  StateMachine* motor_overcurrent() override;
};

#endif // Open_H