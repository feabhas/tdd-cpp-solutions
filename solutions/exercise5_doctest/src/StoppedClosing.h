#ifndef StoppedClosing_H
#define StoppedClosing_H

#include "StateMachine.h"

class StoppedClosing : public StateMachine {
public:
  StoppedClosing();
  ~StoppedClosing();
  StateMachine* button_pressed() override;
  StateMachine* fully_open() override;
  StateMachine* fully_closed() override;
  StateMachine* ir_beam_broken() override;
  StateMachine* motor_overcurrent() override;
};

#endif // StoppedClosing_H