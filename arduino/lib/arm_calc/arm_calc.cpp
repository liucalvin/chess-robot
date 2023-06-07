#include <arm_calc.h>
#include <constants.h>
#include <math.h>

/**
* For sides a, b, c - returns the angle A in degrees.
*/
int cosineLawAngle(float a, float b, float c) {
  return acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0)) / (2.0 * b * c)) * RAD_TO_DEG;
}

/**
* For sides b, c and the angle opposite side c (gamma) in degrees - returns the side length a.
*/
int cosineLawSide(float b, float c, float gammaDeg) {
  return sqrt(pow(b, 2.0) + pow(c, 2.0) - 2.0 * b * c * cos(gammaDeg * DEG_TO_RAD));
}

int calcArm1AngleDeg(float horizontalDistMM) {
  // gamma \ alpha / theta
  float gamma = atan(GRABBER_LEN_MM / horizontalDistMM) * RAD_TO_DEG;

  // cosine law:
  float a = ARM_2_LEN_MM;
  float b = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));
  float c = ARM_1_LEN_MM;

  float theta = cosineLawAngle(a, b, c);

  return 180 - gamma - theta + ARM_1_OFFSET;
}

int calcArm2AngleDeg(float horizontalDistMM) {
  float a = ARM_1_LEN_MM;
  float b = ARM_2_LEN_MM;
  float c = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));

  return cosineLawAngle(c, a, b) + ARM_2_OFFSET;
}
