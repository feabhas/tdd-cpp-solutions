#ifndef TDD

#define LOG
#include "GarageDoorOpener.h"

int main()
{
  GarageDoorOpener garageDoorOpener{};

  garageDoorOpener.button_pressed();
  garageDoorOpener.fully_open();
  garageDoorOpener.button_pressed();
  garageDoorOpener.fully_closed();

}

#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#endif