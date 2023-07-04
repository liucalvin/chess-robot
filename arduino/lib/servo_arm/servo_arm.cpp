#include <Servo.h>
#include <Arduino.h>
#include <constants.h>
#include <servo_arm.h>
#include <math.h>

ServoArm::ServoArm() {}

/**
 * @brief Initializes the object and attaches a new Servo object with the specified properties
 *
 * @param pin - the pin attached to the servo motor
 * @param id - a unique identifier for the arm
 * @param default_angle - angle to which the servo will be set at startup
 * @param min - the minimum allowable angle
 * @param max - the maximum allowable angle
 */
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

/**
 * @brief Rotates the servo to the new position
 *
 * @param new_pos the angle to rotate to, in degrees
 */
void ServoArm::setPosition(int new_pos)
{
  Serial.print("turning motor ");
  Serial.print(id);
  Serial.print(" from ");
  Serial.print(current_pos);
  Serial.print(" to ");
  Serial.print(new_pos);
  Serial.print(" with max ");
  Serial.print(MAX_POS);
  Serial.print(" and min ");
  Serial.println(MIN_POS);

  if (new_pos > current_pos)
  {
    if (new_pos > MAX_POS)
    {
      new_pos = MAX_POS;
    }
    for (; current_pos <= new_pos; current_pos++)
    {
      Serial.print("turning motor ");
      Serial.print(id);
      Serial.print(" from ");
      Serial.print(this->read());
      Serial.print(" to ");
      Serial.println(current_pos);
      this->servo.write(current_pos);
      delay(SERVO_DELAY);
    }
  }
  else
  {
    if (new_pos < MIN_POS)
    {
      new_pos = MIN_POS;
    }
    for (; current_pos >= new_pos && current_pos >= MIN_POS; current_pos--)
    {
      Serial.print("turning motor ");
      Serial.print(id);
      Serial.print(" from ");
      Serial.print(this->read());
      Serial.print(" to ");
      Serial.println(current_pos);
      this->servo.write(current_pos);
      delay(SERVO_DELAY);
    }
  }
}

/**
 * @brief Rotates the servo back to its default angle
 *
 */
void ServoArm::resetPosition()
{
  this->setPosition(DEFAULT_POS);
}

/**
 * @brief Rotates two ServoArm objects to new positions in parallel, linearly
 *
 * @param pos new position of this ServoArm
 * @param other the other ServoArm
 * @param otherPos new position of the other ServoArm
 */
void ServoArm::moveInParallel(int pos, ServoArm &other, int otherPos)
{
  int difference_1 = this->getCurrentPosition() > pos ? -1 : 1;
  int difference_2 = other.getCurrentPosition() > otherPos ? -1 : 1;
  int range_1 = abs(this->getCurrentPosition() - pos);
  int range_2 = abs(other.getCurrentPosition() - otherPos);
  for (size_t i = 0; i < range_1 * range_2; i++)
  {
    if (i % range_1 == 0)
    {
      other.setPosition(other.getCurrentPosition() + difference_2);
    }
    if (i % range_2 == 0)
    {
      this->setPosition(this->getCurrentPosition() + difference_1);
    }
  }
}
