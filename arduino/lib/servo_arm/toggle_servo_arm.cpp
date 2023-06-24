#include <Servo.h>
#include <Arduino.h>
#include <constants.h>
#include <servo_arm.h>
#include <toggle_servo_arm.h>

ToggleServoArm::ToggleServoArm() {}

void ToggleServoArm::toggle()
{
  if (open)
  {
    setPosition(closed_pos);
  }
  else
  {
    setPosition(open_pos);
  }
}
