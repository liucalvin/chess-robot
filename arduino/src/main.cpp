#include <Arduino.h>
#include <Servo.h>
#include <string>
#include <ctype.h>

#include <arm_calc.h>
#include <constants.h>
#include <servo_arm.h>
#include <double_servo_arm.h>
#include <toggle_servo_arm.h>
#include <utils.h>
#include <position_mapper.h>

int servo_arm_1a_pos = SERVO_ARM_1A_DEFAULT;

DoubleServoArm servo_arm_1;
ServoArm servo_arm_2;
ToggleServoArm servo_grabber;
ServoArm servo_rotator;

bool grabber_closed = false;

void print_current_servo_angles()
{
  Serial.println();
  Serial.print("Arm 1 angle:  ");
  Serial.print(servo_arm_1.getCurrentPosition());
  Serial.print("  servo:  ");
  Serial.println(servo_arm_1.read());
  Serial.print("Arm 2 angle:  ");
  Serial.print(servo_arm_2.getCurrentPosition());
  Serial.print("  servo:  ");
  Serial.println(servo_arm_2.read());
  Serial.print("Grabber angle:  ");
  Serial.print(servo_grabber.getCurrentPosition());
  Serial.print("  servo:  ");
  Serial.println(servo_grabber.read());
  Serial.print("Rotator angle:  ");
  Serial.print(servo_rotator.getCurrentPosition());
  Serial.print("  servo:  ");
  Serial.println(servo_rotator.read());
  Serial.println("================");
}

void setup()
{
  Serial.begin(9600);

  servo_arm_1.Init(SERVO_ARM_1A_PIN, SERVO_ARM_1B_PIN, SERVO_ARM_1_ID, SERVO_ARM_1A_DEFAULT, SERVO_ARM_1_MIN, SERVO_ARM_1_MAX);
  servo_arm_2.Init(SERVO_ARM_2_PIN, SERVO_ARM_2_ID, SERVO_ARM_2_DEFAULT, SERVO_ARM_2_MIN, SERVO_ARM_2_MAX);
  servo_grabber.Init(SERVO_GRABBER_PIN, SERVO_GRABBER_ID, SERVO_GRABBER_DEFAULT_OPEN, SERVO_GRABBER_OPEN_POS, SERVO_GRABBER_CLOSED_POS);
  servo_rotator.Init(SERVO_ROTATOR_PIN, SERVO_ROTATOR_ID, SERVO_ROTATOR_DEFAULT, SERVO_ROTATOR_MIN, SERVO_ROTATOR_MAX);

  Serial.println("Ready.");
}

/**
 * @brief Moves the robot according to the specified input,
 *        encoded as [data][selection], with the selection
 *        being only one digit
 *
 * @param input the encoded selection
 */
void handle_selection(int input)
{
  int choice = input % 10;
  int new_pos = input / 10;

  Serial.print("choice: ");
  Serial.println(choice);
  Serial.print("new_pos: ");
  Serial.println(new_pos);
  switch (choice)
  {
  case SERVO_ARM_1_ID:
  {
    servo_arm_1.setPosition(new_pos);
    break;
  }
  case SERVO_ARM_2_ID:
  {
    servo_arm_2.setPosition(new_pos);
    break;
  }
  case SERVO_GRABBER_ID:
  {
    if (grabber_closed)
    {
      servo_grabber.open();
    }
    else
    {
      servo_grabber.close();
    }
    grabber_closed = !grabber_closed;
    break;
  }
  case SERVO_ROTATOR_ID:
  {
    servo_rotator.setPosition(new_pos);
    break;
  }
  case MOVE_IN_PARALLEL_ID:
  {
    int arm_1_pos_parallel = new_pos / 1000;
    int arm_2_pos_parallel = new_pos % 1000;

    Serial.print("moving in parallel. arm 1 pos: ");
    Serial.print(arm_1_pos_parallel);
    Serial.print(", arm_2_pos: ");
    Serial.println(arm_2_pos_parallel);

    servo_arm_1.moveInParallel(arm_1_pos_parallel, servo_arm_2, arm_2_pos_parallel);
    break;
  }
  case CURRENT_POSITION_ID:
  {
    print_current_servo_angles();
    break;
  }
  case DISTANCE_CALC_ID:
  {
    if (new_pos < 1 || new_pos > MAX_ARM_DISTANCE_MM)
    {
      Serial.println("Distance out of range. Please enter a distance between 0 and 440 mm.");
    }
    else
    {
      int arm1AngleDeg = calcArm1AngleFromTop(new_pos);
      Serial.print("Arm 1 angle: ");
      Serial.println(arm1AngleDeg);

      int arm2AngleDeg = calcArm2AngleFromTop(new_pos);
      Serial.print("Arm 2 angle: ");
      Serial.println(arm2AngleDeg);

      auto instructions = PositionMapper::get_instance()->positions_from_distances(new_pos);

      for (int instruction : instructions)
      {
        handle_selection(instruction);
        delay(500);
      }
    }
    break;
  }
  case HANDSHAKE_ID:
  {
    if (Serial.availableForWrite())
    {
      Serial.println("Message received");
    }
    break;
  }
  case RESET_POSITION_ID:
  {
    Serial.println("Resetting all motors to default");

    servo_arm_1.resetPosition();
    servo_arm_2.resetPosition();
    servo_grabber.resetPosition();
    servo_rotator.resetPosition();
    break;
  }
  default:
  {
    Serial.println("Please choose a valid option");
    break;
  }
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    String data = Serial.readString();
    Serial.print("data: ");
    Serial.print(data);
    Serial.println("END data");

    if (is_valid_number(data.c_str()))
    {
      int input = data.toInt();
      handle_selection(input);
    }
    else
    {
      Serial.println("Moving according to instructions.");
      std::string move = data.c_str();
      std::string from = move.substr(0, move.find("-"));
      std::string to = move.substr(move.find("-"), move.length());

      auto instructions = PositionMapper::get_instance()->positions_from_moves({from, to});

      for (int instruction : instructions)
      {
        handle_selection(instruction);
        delay(500);
      }
    }

    print_current_servo_angles();
  }
}
