#include <Arduino.h>
#include <Servo.h>
#include <arm_calc.h>
#include <constants.h>

Servo servo_arm_1;
Servo servo_arm_2;
Servo servo_grabber;
Servo servo_rotator;

int servo_arm_1_pos = SERVO_ARM_1_DEFAULT;
int servo_arm_2_pos = SERVO_ARM_2_DEFAULT;
int servo_grabber_pos = SERVO_GRABBER_DEFAULT;
int servo_rotator_pos = SERVO_ROTATOR_DEFAULT;

void setup() {
  Serial.begin(9600);
  Serial.println(servo_arm_1.read());
  servo_arm_1.write(servo_arm_1_pos);
  servo_arm_1.attach(8);
  servo_arm_1.write(servo_arm_1_pos);
  
  Serial.println(servo_arm_2.read());
  servo_arm_2.write(servo_arm_2_pos);
  servo_arm_2.attach(9);
  servo_arm_2.write(servo_arm_2_pos);
  
//  Serial.println(servo_grabber.read());
//  servo_grabber.write(servo_grabber_pos);
//  servo_grabber.attach(10);
//  servo_grabber.write(servo_grabber_pos);
//  
//  Serial.println(servo_rotator.read());
//  servo_rotator.write(pos);
//  servo_rotator.attach(11);
//  servo_rotator.write(pos);
  
  Serial.println("START");
}

void loop() {
  if (Serial.available() > 0) {
    Serial.print("current positions: ");
    Serial.print("arm 1: ");
    Serial.println(servo_arm_1.read());
    Serial.print("arm 2: ");
    Serial.println(servo_arm_2.read());

    int input = Serial.parseInt();
    int choice = input % 10;
    int angle = input / 10;
    
    Serial.print("input: ");
    Serial.println(input);
    Serial.print("choice: ");
    Serial.println(choice);
    Serial.print("angle: ");
    Serial.println(angle);
    switch(choice) {
      case 1:
        setPosition(choice, angle, servo_arm_1_pos, servo_arm_1);
      break;
      case 2:
        setPosition(choice, angle, servo_arm_2_pos, servo_arm_2);
      break;
      case 3:
        Serial.println("turning motor 3");
      break;
      case 7: {
        int arm1AngleDeg = calcArm1AngleDeg(angle);
        Serial.print("Arm 1 angle: ");
        Serial.println(arm1AngleDeg);
        int arm2AngleDeg = calcArm2AngleDeg(angle, arm1AngleDeg);
        Serial.print("Arm 2 angle: ");
        Serial.println(arm2AngleDeg);
        setPosition(1, arm1AngleDeg, servo_arm_1_pos, servo_arm_1);
        setPosition(2, arm2AngleDeg, servo_arm_2_pos, servo_arm_2);
        break;
      }
      case 9: {
        Serial.println("resetting all motors to default");
        setPosition(1, SERVO_ARM_1_DEFAULT, servo_arm_1_pos, servo_arm_1);
        setPosition(2, SERVO_ARM_2_DEFAULT, servo_arm_2_pos, servo_arm_2);
//        setPosition(3, angle, servo_arm_1_pos, servo_arm_1);
//        setPosition(4, angle, servo_arm_1_pos, servo_arm_1);
        break; 
      }
      default:
        Serial.println("choose a valid option");
      break;
    }
  }
}

void setPosition(int choice, int angle, int& servo_pos, Servo servo) {
  Serial.print("turning motor ");
  Serial.print(choice);
  Serial.print(" from ");
  Serial.print(servo_pos);
  Serial.print(" to ");
  Serial.println(angle);

  if (angle > servo_pos) {
    for (; servo_pos <= angle; servo_pos += 1) {
      servo.write(servo_pos);
      delay(SERVO_DELAY);
      Serial.print("motor ");
      Serial.print(choice);
      Serial.print(" current position: ");
      Serial.println(servo.read());
    }
  } else {
    for (; servo_pos >= angle; servo_pos -= 1) {
      servo.write(servo_pos);
      delay(SERVO_DELAY);
      Serial.print("motor ");
      Serial.print(choice);
      Serial.print(" current position: ");
      Serial.println(servo.read());
    }
  }
}
