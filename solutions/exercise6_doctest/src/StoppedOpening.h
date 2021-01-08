#ifndef StoppedOpening_H
#define StoppedOpening_H

#include "StateMachine.h"

class StoppedOpening : public StateMachine {
public:
  StoppedOpening();
  ~StoppedOpening();
  StateMachine* button_pressed() override;
  StateMachine* fully_open() override;
  StateMachine* fully_closed() override;
  StateMachine* ir_beam_broken() override;
  StateMachine* motor_overcurrent() override;
};

#endif // StoppedOpening_H