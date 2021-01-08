#ifndef MOTOR_H
#define MOTOR_H

class I_Motor {
public:
  enum Direction { cw, acw };
  virtual void run(Direction) = 0;
  virtual void stop()         = 0;
  virtual ~I_Motor()          = default;
};

#endif // MOTOR_H