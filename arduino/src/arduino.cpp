#include "Arduino.h"
#include "Servo.h"

void setPosition(int choice, int angle, int& servo_pos, Servo servo);

int calcArm1AngleDeg(float horizontalDistMM);

int cool(int arm1Angle);

int calcArm2AngleDeg(float horizontalDistMM, int arm1AngleDeg);

Servo servo_arm_1;
Servo servo_arm_2;
Servo servo_grabber;
Servo servo_rotator;

constexpr int SERVO_ARM_1_DEFAULT = 120;
constexpr int SERVO_ARM_1_MIN = 30;
constexpr int SERVO_ARM_1_MAX = 130;

// 10 degrees off, 190 degrees = parallel with arm 1
constexpr int SERVO_ARM_2_DEFAULT = 40;
constexpr int SERVO_ARM_2_MIN = 30;
constexpr int SERVO_ARM_2_MAX = 160;

constexpr int SERVO_GRABBER_DEFAULT = 0;
constexpr int SERVO_GRABBER_MIN = 50;
constexpr int SERVO_GRABBER_MAX = 50;

constexpr int SERVO_ROTATOR_DEFAULT = 0;
constexpr int SERVO_ROTATOR_MIN = 50;
constexpr int SERVO_ROTATOR_MAX = 50;

constexpr int SERVO_DELAY = 30;

constexpr float ARM_1_LEN_MM = 231.0;
constexpr float ARM_2_LEN_MM = 223.0;
constexpr float GRABBER_LEN_MM = 97.0; // this is the height of where arm 2 will end up

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

int calcArm1AngleDeg(float horizontalDistMM) {
  // gamma \ alpha / theta
  float gamma = atan((float) GRABBER_LEN_MM / (float) horizontalDistMM) * RAD_TO_DEG;

  // cosine law:
  float a = ARM_2_LEN_MM;
  float b = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));
  float c = ARM_1_LEN_MM;

  float theta = acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0)) / (2.0 * b * c)) * RAD_TO_DEG;

  return 180 - gamma - theta;
}

int cool(int arm1Angle) {
  Serial.print("cool beans");
  Serial.println(arm1Angle);
  return arm1Angle + 1;
}

int calcArm2AngleDeg(float horizontalDistMM, int arm1AngleDeg) {
  float a = ARM_2_LEN_MM;
  float b = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));
  
  // offset by 10
  return asin(b * sin((float) arm1AngleDeg * DEG_TO_RAD) / a) * RAD_TO_DEG + 10;
}
