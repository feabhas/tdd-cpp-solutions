#include "Open.h"

#include <iostream>
using namespace std;

#include "Closing.h"

Open::Open()
{
//  cout << "Door is fully open" << endl;
}
Open::~Open()
{
}

StateMachine* Open::button_pressed()
{
  return StateMachine::transition_to<Closing>();
}
StateMachine* Open::fully_open()
{
  return StateMachine::no_transition();
}
StateMachine* Open::fully_closed()
{
  return StateMachine::illegal_transition();
}

StateMachine* Open::ir_beam_broken()
{
    return StateMachine::illegal_transition();
}

StateMachine* Open::motor_overcurrent() 
{
	return StateMachine::illegal_transition();
}