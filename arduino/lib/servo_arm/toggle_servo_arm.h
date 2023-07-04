#ifndef TOGGLE_SERVO_ARM
#define TOGGLE_SERVO_ARM

#include <Servo.h>
#include <servo_arm.h>

class ToggleServoArm : public ServoArm
{
private:
  bool currently_open;

public:
  ToggleServoArm();
  void Init(int pin, int id, bool default_open, int open_pos, int closed_pos);
  void toggle();
  void open();
  void close();
};

#endif
