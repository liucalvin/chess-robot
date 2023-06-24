#ifndef TOGGLE_SERVO_ARM
#define TOGGLE_SERVO_ARM

#include <Servo.h>
#include <servo_arm.h>

class ToggleServoArm : public ServoArm
{
private:
  bool open;
  int open_pos;
  int closed_pos;

public:
  ToggleServoArm();
  void toggle();
};

#endif
