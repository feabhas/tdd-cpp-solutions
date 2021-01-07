#include "GarageDoorOpener.h"
#include "StateMachine.h"

void GarageDoorOpener::button_pressed()
{
  current_state = current_state->button_pressed();
}

void GarageDoorOpener::fully_open()
{
  current_state = current_state->fully_open();
}

void GarageDoorOpener::fully_closed()
{
  current_state = current_state->fully_closed();
}

void GarageDoorOpener::ir_beam_broken()
{
  current_state = current_state->ir_beam_broken();
}
void GarageDoorOpener::motor_overcurrent()
{
  current_state = current_state->motor_overcurrent();
}

GarageDoorOpener::GarageDoorOpener() : current_state{ StateMachine::initialise() } {}

GarageDoorOpener::~GarageDoorOpener()
{
  StateMachine::terminate(current_state);
}

bool GarageDoorOpener::door_is_closed()
{
	return current_state->doorIsClosed(current_state);
}

bool GarageDoorOpener::door_is_open()
{
	return current_state->doorIsOpen(current_state);
}
