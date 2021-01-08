#include "Closed.h"

#include <iostream>
using namespace std;

#include "Opening.h"

Closed::Closed()
{
//  cout << "Door Closed" << endl;
}
Closed::~Closed()
{
}

StateMachine* Closed::button_pressed()
{
  return StateMachine::transition_to<Opening>();
}

StateMachine* Closed::fully_open()
{
  return StateMachine::illegal_transition();
}

StateMachine* Closed::fully_closed()
{
  return StateMachine::illegal_transition();
}

StateMachine* Closed::ir_beam_broken()
{
    return StateMachine::illegal_transition();
}
StateMachine* Closed::motor_overcurrent() 
{
	return StateMachine::illegal_transition();
}
