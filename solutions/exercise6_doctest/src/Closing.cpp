#include "Closing.h"

#include <iostream>
using namespace std;

#include "Closed.h"
#include "StoppedClosing.h"

Closing::Closing()
{
//  cout << "Door is Closing" << endl;
}
Closing::~Closing()
{
}

StateMachine* Closing::fully_closed()
{
  return StateMachine::transition_to<Closed>();
}

StateMachine* Closing::button_pressed()
{
  return StateMachine::transition_to<StoppedClosing>();
}
StateMachine* Closing::fully_open()
{
  return StateMachine::illegal_transition();
}

StateMachine* Closing::ir_beam_broken()
{
  return StateMachine::transition_to<StoppedClosing>();
}
StateMachine* Closing::motor_overcurrent() 
{
  return StateMachine::transition_to<StoppedClosing>();
}