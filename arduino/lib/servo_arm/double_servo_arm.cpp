#include <Servo.h>
#include <Arduino.h>
#include <constants.h>
#include <servo_arm.h>
#include <double_servo_arm.h>

DoubleServoArm::DoubleServoArm() {}

/**
 * @brief Initializes the object and attaches two synced servos with the specified properties
 *
 * @param pin           the pin that the forward-rotating (0 to 180) servo is attached to
 * @param reverse_pin   the pin that the reverse-rotating (180 to 0) servo is attached to
 * @param id            a unique identifier for the arm
 * @param default_angle angle to which the servo will be set at startup
 * @param min           the minimum allowable angle (for the forward-rotating servo)
 * @param max           the maximum allowable angle (for the forward-rotating servo)
 * @return * void
 */
void DoubleServoArm::Init(int forward_pin, int reverse_pin, int id, int default_angle, int min, int max)
{
  this->pin = forward_pin;
  this->reverse_pin = reverse_pin;
  this->id = id;
  DEFAULT_POS = default_angle;
  current_pos = DEFAULT_POS;
  MIN_POS = min;
  MAX_POS = max;

  servo.write(DEFAULT_POS);
  servo_reverse.write(MAX_POS - DEFAULT_POS);

  servo.attach(pin, Servo::CHANNEL_NOT_ATTACHED, min, max);
  servo_reverse.attach(reverse_pin, Servo::CHANNEL_NOT_ATTACHED, min, max);

  servo.write(DEFAULT_POS);
  servo_reverse.write(MAX_POS - DEFAULT_POS);
}

/**
 * @brief Rotates both servos in sync to the new position
 *
 * @param new_pos the angle to rotate to, in degrees
 */
void DoubleServoArm::setPosition(int new_pos)
{
  Serial.print("turning motor ");
  Serial.print(id);
  Serial.print(" from ");
  Serial.print(current_pos);
  Serial.print(" to ");
  Serial.println(new_pos);

  if (new_pos > current_pos)
  {
    for (; current_pos <= new_pos && current_pos <= SERVO_ARM_1_MAX; current_pos++)
    {
      servo.write(current_pos);
      servo_reverse.write(SERVO_ARM_1_MAX - current_pos);
      delay(SERVO_DELAY);
    }
  }
  else
  {
    for (; current_pos >= new_pos && current_pos >= SERVO_ARM_1_MIN; current_pos--)
    {
      servo.write(current_pos);
      servo_reverse.write(SERVO_ARM_1_MAX - current_pos);
      delay(SERVO_DELAY);
    }
  }
}

/**
 * @brief Rotates the servo back to its default angle
 * 
 */
void DoubleServoArm::resetPosition()
{
  this->setPosition(DEFAULT_POS);
}
