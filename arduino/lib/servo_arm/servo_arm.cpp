#include <Servo.h>
#include <Arduino.h>
#include <constants.h>
#include <servo_arm.h>

ServoArm::ServoArm() {}

void ServoArm::Init(int pin, int id, int default_angle, int min, int max) {
  this->pin = pin;
  this->id = id;
  DEFAULT_POS = default_angle;
  current_pos = DEFAULT_POS;
  MIN_POS = min;
  MAX_POS = max;

  servo.write(DEFAULT_POS);
  servo.attach(pin);
  // servo.write(DEFAULT_POS);
}

int ServoArm::getCurrentPosition() {
  return current_pos;
}

void ServoArm::setPosition(int new_pos) {
  Serial.print("turning motor ");
  Serial.print(id);
  Serial.print(" from ");
  Serial.print(current_pos);
  Serial.print(" to ");
  Serial.println(new_pos);

  if (new_pos > current_pos) {
    for (int i = current_pos; i <= new_pos && i <= MAX_POS; i += 1) {
      servo.write(i);
      delay(SERVO_DELAY);
    }
    if (new_pos > MAX_POS) {
      current_pos = MAX_POS;
    } else {
      current_pos = new_pos;
    }
  } else {
    for (int i = current_pos; i >= new_pos && i >= MIN_POS; i -= 1) {
      servo.write(i);
      delay(SERVO_DELAY);
    }
    if (new_pos < MIN_POS) {
      current_pos = MIN_POS;
    } else {
      current_pos = new_pos;
    }
  }
}


void ServoArm::resetPosition() {
  this->setPosition(DEFAULT_POS);
}
