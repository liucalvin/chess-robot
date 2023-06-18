#include <Servo.h>
#include <Arduino.h>
#include <constants.h>
#include <servo_arm.h>

ServoArm::ServoArm() {}

void ServoArm::Init(int pin, int id, int default_angle, int min, int max)
{
  this->pin = pin;
  this->id = id;
  DEFAULT_POS = default_angle;
  current_pos = DEFAULT_POS;
  MIN_POS = min;
  MAX_POS = max;

  servo.write(DEFAULT_POS);
  servo.attach(pin, Servo::CHANNEL_NOT_ATTACHED, min, max);
  servo.write(DEFAULT_POS);
}

int ServoArm::getCurrentPosition()
{
  return current_pos;
}

int ServoArm::read()
{
  return servo.read();
}

void ServoArm::setPosition(int new_pos)
{
  Serial.print("turning motor ");
  Serial.print(id);
  Serial.print(" from ");
  Serial.print(current_pos);
  Serial.print(" to ");
  Serial.println(new_pos);

  if (new_pos > current_pos)
  {
    if (new_pos > MAX_POS)
    {
      new_pos = MAX_POS;
    }
    for (; current_pos <= new_pos; current_pos += 1)
    {
      servo.write(current_pos);
      delay(SERVO_DELAY);
    }
  }
  else
  {
    if (new_pos < MIN_POS)
    {
      new_pos = MIN_POS;
    }
    for (; current_pos >= new_pos && current_pos >= MIN_POS; current_pos -= 1)
    {
      servo.write(current_pos);
      delay(SERVO_DELAY);
    }
  }
}

void ServoArm::resetPosition()
{
  this->setPosition(DEFAULT_POS);
}
