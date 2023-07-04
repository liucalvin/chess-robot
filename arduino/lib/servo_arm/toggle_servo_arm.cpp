#include <Servo.h>
#include <Arduino.h>
#include <constants.h>
#include <servo_arm.h>
#include <toggle_servo_arm.h>

ToggleServoArm::ToggleServoArm() {}

/**
 * @brief Initializes the object and attaches a new Servo object with the specified properties
 *
 * @param pin - the pin attached to the servo motor
 * @param id - a unique identifier for the arm
 * @param default_open - whether the arm is open at startup
 * @param open_pos - angle when the grabber is open
 * @param closed_pos - angle when the grabber is closed
 */
void ToggleServoArm::Init(int pin, int id, bool default_open, int open_pos, int closed_pos)
{
  this->pin = pin;
  this->id = id;
  this->currently_open = default_open;
  DEFAULT_POS = default_open ? open_pos : closed_pos;
  current_pos = DEFAULT_POS;
  MIN_POS = open_pos;
  MAX_POS = closed_pos;

  servo.write(DEFAULT_POS);
  servo.attach(pin, Servo::CHANNEL_NOT_ATTACHED, open_pos, closed_pos);
  servo.write(DEFAULT_POS);
}

void ToggleServoArm::toggle()
{
  if (this->currently_open)
  {
    setPosition(MAX_POS);
  }
  else
  {
    setPosition(MIN_POS);
  }
  this->currently_open = !this->currently_open;
}

void ToggleServoArm::open()
{
  servo.write(MIN_POS);
}

void ToggleServoArm::close()
{
  setPosition(MAX_POS);
}
