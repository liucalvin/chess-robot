#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

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

constexpr int ARM_1_OFFSET = 0;
constexpr int ARM_2_OFFSET = -10;

#endif
