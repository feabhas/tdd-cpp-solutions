#ifndef StateMachine_H
#define StateMachine_H

#include <iostream>

class StateMachine {
public:
  static StateMachine* initialise();
  static void          terminate(StateMachine* stateMachine);

  virtual StateMachine* button_pressed() = 0;
  virtual StateMachine* fully_open() = 0;
  virtual StateMachine* fully_closed() = 0;
  virtual StateMachine* ir_beam_broken() = 0;
  virtual StateMachine* motor_overcurrent() = 0;

  bool doorIsClosed(StateMachine* current_state);
  bool doorIsOpen(StateMachine* current_state);

  virtual ~StateMachine() = default;

protected:
  template<typename State_Ty>
  StateMachine* transition_to();

  StateMachine* no_transition();
  StateMachine* illegal_transition();
};

#if 0
template<typename State_Ty>
StateMachine* StateMachine::transition_to()
{
  delete this;
#ifdef LOG
  std::cout << typeid(State_Ty).name() << std::endl;
#endif
  return new State_Ty { };
}
#else
template<typename State_Ty>
StateMachine* StateMachine::transition_to()
{
#ifdef LOG
  std::cout << typeid(State_Ty).name() << std::endl;
#endif
  // Create the new StateMachine object
  // directly into the memory of the
  // old one.  This only works because
  // all StateMachine objects are the same
  // size.
  //
  return new (this) State_Ty;
}
#endif


#endif // StateMachine_H