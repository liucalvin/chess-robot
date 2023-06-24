#ifndef DOUBLE_SERVO_ARM
#define DOUBLE_SERVO_ARM

#include <Servo.h>
#include <servo_arm.h>

class DoubleServoArm : public ServoArm
{
private:
  Servo servo_reverse;
  int reverse_pin;

public:
  DoubleServoArm();
  void Init(int forward_pin, int reverse_pin, int id, int default_angle, int min, int max);
  void setPosition(int new_pos) override;
  void resetPosition() override;
};

#endif
