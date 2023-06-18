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

constexpr int SERVO_GRABBER_OPEN_POS = 160;
constexpr int SERVO_GRABBER_CLOSED_POS = 180;
constexpr int SERVO_GRABBER_DEFAULT = SERVO_GRABBER_OPEN_POS;
constexpr int SERVO_GRABBER_MIN = 160;
constexpr int SERVO_GRABBER_MAX = 180;

constexpr int SERVO_ROTATOR_DEFAULT = 120;
constexpr int SERVO_ROTATOR_MIN = 0;
constexpr int SERVO_ROTATOR_MAX = 180;

constexpr int SERVO_DELAY = 30;

constexpr float ARM_1_LEN_MM = 231.0;
constexpr float ARM_2_LEN_MM = 223.0;
constexpr float GRABBER_LEN_MM = 107.0; // this is the height of where arm 2 will end up
constexpr float MAX_ARM_DISTANCE_MM = 440.0;

constexpr int ARM_1_OFFSET = 0;
// 10 degrees off, 190 degrees = parallel with arm 1
// so 190 + offset = 180
constexpr int ARM_2_OFFSET = -10;

#endif
