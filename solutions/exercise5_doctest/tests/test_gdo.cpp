#include "doctest.h"

#include "GarageDoorOpener.h"
#include <exception>


 TEST_CASE("Door initially closed")
 {
   GarageDoorOpener garageDoorOpener{};
   CHECK(garageDoorOpener.door_is_closed() == true);
   CHECK(garageDoorOpener.door_is_open() == false);
 }

SCENARIO("Normal operation - remote open")
{
  GarageDoorOpener garageDoorOpener{};

  GIVEN("the door is fully closed") {
    REQUIRE(garageDoorOpener.door_is_closed() == true);

    AND_WHEN( "the owner presses the remote button" ) {
      garageDoorOpener.button_pressed();

      AND_THEN( "the door is fully open" ) {
        garageDoorOpener.fully_open();
        CHECK(garageDoorOpener.door_is_open() == true);
      }
    }
  }
}

 TEST_CASE("Close to Open to Closed")
 {
   GarageDoorOpener garageDoorOpener{};

   garageDoorOpener.button_pressed();
   CHECK(garageDoorOpener.door_is_closed() == false);
   CHECK(garageDoorOpener.door_is_open() == false);

   garageDoorOpener.fully_open();
   CHECK(garageDoorOpener.door_is_closed() == false);
   CHECK(garageDoorOpener.door_is_open() == true);

   garageDoorOpener.button_pressed();
   CHECK(garageDoorOpener.door_is_closed() == false);
   CHECK(garageDoorOpener.door_is_open() == false);

   garageDoorOpener.fully_closed();
   CHECK(garageDoorOpener.door_is_closed() == true);
   CHECK(garageDoorOpener.door_is_open() == false);
 }


 TEST_CASE("Close to Stopped Opening to Closed")
 {
   GarageDoorOpener garageDoorOpener{};

   garageDoorOpener.button_pressed();
   CHECK(garageDoorOpener.door_is_closed() == false);

   garageDoorOpener.button_pressed();
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_closed();
   CHECK(garageDoorOpener.door_is_closed() == true);
 }

 TEST_CASE("Close -> Stopped Closing (button) ->  Closed")
 {
   GarageDoorOpener garageDoorOpener{};

   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_open();
   garageDoorOpener.button_pressed();

   // halt closing
   garageDoorOpener.button_pressed();

   // resume opening
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_open();
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_closed();
   CHECK(garageDoorOpener.door_is_closed() == true);
 }

 TEST_CASE("Close -> Stopped Closing (motor overcurrent) ->  Closed")
 {
   GarageDoorOpener garageDoorOpener{};

   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_open();
   garageDoorOpener.button_pressed();

   // halt closing
   garageDoorOpener.motor_overcurrent();

   // resume opening
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_open();
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_closed();
   CHECK(garageDoorOpener.door_is_closed() == true);
 }

 TEST_CASE("Close -> Stopped Closing (ir) ->  Closed")
 {
   GarageDoorOpener garageDoorOpener{};

   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_open();
   garageDoorOpener.button_pressed();

   // halt closing
   garageDoorOpener.ir_beam_broken();

   // resume opening
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_open();
   garageDoorOpener.button_pressed();
   garageDoorOpener.fully_closed();
   CHECK(garageDoorOpener.door_is_closed() == true);
 }

 TEST_CASE("A closed door cannot transition directly to fully open")
 {
   GarageDoorOpener garageDoorOpener{};
   CHECK_THROWS_AS(garageDoorOpener.fully_open(), std::exception);
 }