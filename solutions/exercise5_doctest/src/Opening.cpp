#include "Opening.h"

#include <iostream>
using namespace std;

#include "Open.h"
#include "StoppedOpening.h"

Opening::Opening()
{
//  cout << "Door is opening" << endl;
}
Opening::~Opening()
{
}

StateMachine* Opening::button_pressed()
{
  return StateMachine::transition_to<StoppedOpening>();
}
StateMachine* Opening::fully_open()
{
  return StateMachine::transition_to<Open>();
}
StateMachine* Opening::fully_closed()
{
  return StateMachine::illegal_transition();
}
StateMachine* Opening::ir_beam_broken()
{
    return StateMachine::illegal_transition();
}
StateMachine* Opening::motor_overcurrent() 
{
  return StateMachine::transition_to<StoppedOpening>();
}