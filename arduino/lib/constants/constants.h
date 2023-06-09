#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

// SELECTIONS
constexpr int SERVO_ARM_1_ID = 1;
constexpr int SERVO_ARM_2_ID = 2;
constexpr int SERVO_GRABBER_ID = 3;
constexpr int SERVO_ROTATOR_ID = 4;
constexpr int CURRENT_POSITION_ID = 5;
constexpr int MOVE_IN_PARALLEL_ID = 6;
constexpr int DISTANCE_CALC_ID = 7;
constexpr int HANDSHAKE_ID = 8;
constexpr int RESET_POSITION_ID = 9;

// PINS
// pins: 33 14 15 16 18
constexpr int SERVO_ARM_1A_PIN = 14;
constexpr int SERVO_ARM_1B_PIN = 15;
constexpr int SERVO_ARM_2_PIN = 18;
constexpr int SERVO_GRABBER_PIN = 16;
constexpr int SERVO_ROTATOR_PIN = 33;

/**
 * How the offset works:
 * Arm 1A adds this offset to its position to be in line
 * with arm 1B.
 *
 * For theoretical_arm_1a_pos (what is calculated) and
 * real_arm_1a_pos (what the servo motor is at) we have
 *
 * theoretical_arm_1a_pos = real_arm_1a_pos + ARM_1A_OFFSET
 * real_arm_1a_pos + ARM_1A_OFFSET = 180 - arm_1b_pos
 * so: theoretical_arm_1a_pos = 180 - arm_1b_pos
 *
 * (If they were perfectly inline, then real_arm_1a_pos = 180 - arm_1b_pos)
 *
 * Arm 1A range is 160 to 0 degrees
 * Arm 1B range is 0 to 160 degrees
 */
constexpr int ARM_1A_OFFSET = 10;

constexpr int SERVO_ARM_1A_DEFAULT = 90;
constexpr int SERVO_ARM_1_MIN = 0;
constexpr int SERVO_ARM_1_MAX = 180 - ARM_1A_OFFSET;

constexpr int SERVO_ARM_2_DEFAULT = 126;
constexpr int SERVO_ARM_2_MIN = 30;
constexpr int SERVO_ARM_2_MAX = 180;

constexpr int SERVO_GRABBER_OPEN_POS = 100;
constexpr int SERVO_GRABBER_CLOSED_POS = 150;
constexpr int SERVO_GRABBER_DEFAULT_OPEN = true;

constexpr int SERVO_ROTATOR_DEFAULT = 80;
constexpr int SERVO_ROTATOR_MIN = 0;
constexpr int SERVO_ROTATOR_MAX = 180;

constexpr int SERVO_DELAY = 20;

constexpr float ARM_1_LEN_MM = 233.0;
constexpr float ARM_2_LEN_MM = 224.0;
constexpr float GRABBER_LEN_MM = 107.0; // this is the height of where arm 2 will end up
constexpr float MAX_ARM_DISTANCE_MM = 440.0;
constexpr float HEIGHT = 386.0;
constexpr float SQUARE_WIDTH = 48.5;

// 90 is 37 on the motor -> add -53 to theoretical to get motor position
constexpr int ARM_1_OFFSET = -53;
// 90 is 108 on the motor -> add 18 to theoretical to get motor position
constexpr int ARM_2_OFFSET = 18;

#endif
