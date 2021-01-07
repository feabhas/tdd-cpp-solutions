#include "StateMachine.h"

#include "Closed.h"
#include "Open.h"

#include <typeinfo>
#include <exception>

StateMachine* StateMachine::initialise()
{
  return new Closed;
}

void StateMachine::terminate(StateMachine* state)
{
  delete state;
}

StateMachine* StateMachine::no_transition()
{
  return this;
}

StateMachine* StateMachine::illegal_transition()
{
	throw std::domain_error("illegal transition");
  return this;
}
bool StateMachine::doorIsClosed(StateMachine* current_state)
{
	return (typeid(*current_state) == typeid(Closed));
}

bool StateMachine::doorIsOpen(StateMachine* current_state)
{
	return (typeid(*current_state) == typeid(Open));
}