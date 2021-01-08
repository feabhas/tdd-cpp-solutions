#include "StoppedClosing.h"

#include <iostream>
using namespace std;

#include "Opening.h"

StoppedClosing::StoppedClosing()
{
//  cout << "Door is StoppedClosing" << endl;
}
StoppedClosing::~StoppedClosing()
{
}

StateMachine* StoppedClosing::button_pressed()
{
  return StateMachine::transition_to<Opening>();
}
StateMachine* StoppedClosing::fully_open()
{
  return StateMachine::illegal_transition();
}
StateMachine* StoppedClosing::fully_closed()
{
  return StateMachine::illegal_transition();
}
StateMachine* StoppedClosing::ir_beam_broken()
{
    return StateMachine::illegal_transition();
}
StateMachine* StoppedClosing::motor_overcurrent() 
{
	return StateMachine::illegal_transition();
}