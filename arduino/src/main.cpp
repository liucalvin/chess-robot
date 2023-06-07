#include <Arduino.h>
#include <Servo.h>
#include <arm_calc.h>
#include <constants.h>
#include <servo_arm.h>

int servo_arm_1_pos = SERVO_ARM_1_DEFAULT;

Servo servo_arm_1a;
Servo servo_arm_1b;
ServoArm servo_arm_2;
ServoArm servo_grabber;

bool grabber_closed = false;

void setup() {
  Serial.begin(9600);

  servo_arm_1a.write(servo_arm_1_pos);
  servo_arm_1a.attach(8);
  // servo_arm_1a.write(servo_arm_1_pos);
  servo_arm_1b.write(180 - servo_arm_1_pos);
  servo_arm_1b.attach(9);
  // servo_arm_1b.write(180 - servo_arm_1_pos);

  servo_arm_2.Init(10, SERVO_ARM_2_ID, SERVO_ARM_2_DEFAULT, SERVO_ARM_2_MIN, SERVO_ARM_2_MAX);
  servo_grabber.Init(11, SERVO_GRABBER_ID, SERVO_GRABBER_DEFAULT, SERVO_GRABBER_MIN, SERVO_GRABBER_MAX);

  Serial.println("START");
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    Serial.println((String) "data: " + data);
    int input = data.toInt();
    Serial.println((String) "input: " + input);

    int choice = input % 10;
    int new_pos = input / 10;
    
    // Serial.print("choice: ");
    // Serial.println(choice);
    // Serial.print("new_pos: ");
    // Serial.println(new_pos);
    switch(choice) {
      case SERVO_ARM_1_ID:
          Serial.print("turning arm from ");
          Serial.print(servo_arm_1_pos);
          Serial.print(" to ");
          Serial.println(new_pos);

          if (new_pos > servo_arm_1_pos) {
            for (; servo_arm_1_pos <= new_pos && servo_arm_1_pos <= SERVO_ARM_1_MAX; servo_arm_1_pos += 1) {
              servo_arm_1a.write(servo_arm_1_pos);
              servo_arm_1b.write(180 - servo_arm_1_pos);
              delay(SERVO_DELAY);
            }
          } else {
            for (; servo_arm_1_pos >= new_pos && servo_arm_1_pos >= SERVO_ARM_1_MIN; servo_arm_1_pos -= 1) {
              servo_arm_1a.write(servo_arm_1_pos);
              servo_arm_1b.write(180 - servo_arm_1_pos);
              delay(SERVO_DELAY);
            }
          }
      break;
      case SERVO_ARM_2_ID:
        servo_arm_2.setPosition(new_pos);
      break;
      case SERVO_GRABBER_ID:
        int new_position;
        if (grabber_closed) {
          new_position = SERVO_GRABBER_OPEN_POS;
        } else {
          new_position = SERVO_GRABBER_CLOSED_POS;
        }

        servo_grabber.setPosition(new_position);
        grabber_closed = !grabber_closed;
      break;
      case CURRENT_POSITION_ID: {
        Serial.print("Arm 1 angle: ");
        Serial.println(servo_arm_1.getCurrentPosition());
        Serial.print("Arm 2 angle: ");
        Serial.println(servo_arm_2.getCurrentPosition());
        Serial.print("Grabber angle: ");
        Serial.println(servo_grabber.getCurrentPosition());
        break;
      }
      case DISTANCE_CALC_ID: {
        int arm1AngleDeg = calcArm1AngleDeg(new_pos);
        Serial.print("Arm 1 angle: ");
        Serial.println(arm1AngleDeg);
        
        int arm2AngleDeg = calcArm2AngleDeg(new_pos, arm1AngleDeg);
        Serial.print("Arm 2 angle: ");
        Serial.println(arm2AngleDeg);

        servo_arm_1.setPosition(arm1AngleDeg);
        servo_arm_2.setPosition(arm2AngleDeg);
      break;
      }
      case HANDSHAKE_ID: {
        if (Serial.availableForWrite()) {
          Serial.println("Message received");
        }
      break;
      }
      case RESET_POSITION_ID: {
        Serial.println("Resetting all motors to default");
        servo_arm_1.resetPosition();
        servo_arm_2.resetPosition();
        servo_grabber.resetPosition();
      break; 
      }
      default:
        Serial.println("Please choose a valid option");
      break;
    }
  }
}
