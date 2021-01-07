#include "StoppedOpening.h"

#include <iostream>
using namespace std;

#include "Closing.h"

StoppedOpening::StoppedOpening()
{
//  cout << "Door is StoppedOpening" << endl;
}
StoppedOpening::~StoppedOpening()
{
}

StateMachine* StoppedOpening::button_pressed()
{
  return StateMachine::transition_to<Closing>();
}
StateMachine* StoppedOpening::fully_open()
{
  return StateMachine::illegal_transition();
}
StateMachine* StoppedOpening::fully_closed()
{
  return StateMachine::illegal_transition();
}
StateMachine* StoppedOpening::ir_beam_broken()
{
    return StateMachine::illegal_transition();
}
StateMachine* StoppedOpening::motor_overcurrent() 
{
	return StateMachine::illegal_transition();
}