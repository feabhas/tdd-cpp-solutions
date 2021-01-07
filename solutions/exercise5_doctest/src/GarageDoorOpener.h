#ifndef GarageDoorOpener_H
#define GarageDoorOpener_H

class StateMachine;

class GarageDoorOpener {
public:
  GarageDoorOpener();
  ~GarageDoorOpener();

  void button_pressed();
  void fully_open();
  void fully_closed();
  void ir_beam_broken();
  void motor_overcurrent();

  bool door_is_closed();
  bool door_is_open();

private:
  StateMachine* current_state;
};

#endif // GarageDoorOpener_H