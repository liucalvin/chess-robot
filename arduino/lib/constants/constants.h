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

constexpr int SERVO_ARM_1_DEFAULT = 115;
constexpr int SERVO_ARM_1_MIN = 30;
constexpr int SERVO_ARM_1_MAX = 130;

constexpr int SERVO_ARM_2_DEFAULT = 40;
constexpr int SERVO_ARM_2_MIN = 30;
constexpr int SERVO_ARM_2_MAX = 160;

constexpr int SERVO_GRABBER_OPEN_POS = 160;
constexpr int SERVO_GRABBER_CLOSED_POS = 180;
constexpr int SERVO_GRABBER_DEFAULT = SERVO_GRABBER_OPEN_POS;
constexpr int SERVO_GRABBER_MIN = 135;
constexpr int SERVO_GRABBER_MAX = 180;

constexpr int SERVO_ROTATOR_DEFAULT = 0;
constexpr int SERVO_ROTATOR_MIN = 50;
constexpr int SERVO_ROTATOR_MAX = 50;

constexpr int SERVO_DELAY = 30;

constexpr float ARM_1_LEN_MM = 231.0;
constexpr float ARM_2_LEN_MM = 223.0;
constexpr float GRABBER_LEN_MM = 107.0; // this is the height of where arm 2 will end up

constexpr int ARM_1_OFFSET = 0;
// 10 degrees off, 190 degrees = parallel with arm 1
// so 190 + offset = 180 
constexpr int ARM_2_OFFSET = -10;

#endif
