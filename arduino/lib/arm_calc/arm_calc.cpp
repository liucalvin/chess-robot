#include <arm_calc.h>
#include <constants.h>
#include <math.h>

int calcArm1AngleDeg(float horizontalDistMM) {
  // gamma \ alpha / theta
  float gamma = atan((float) GRABBER_LEN_MM / (float) horizontalDistMM) * RAD_TO_DEG;

  // cosine law:
  float a = ARM_2_LEN_MM;
  float b = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));
  float c = ARM_1_LEN_MM;

  float theta = acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0)) / (2.0 * b * c)) * RAD_TO_DEG;

  return 180 - gamma - theta + ARM_1_OFFSET;
}

int calcArm2AngleDeg(float horizontalDistMM, int arm1AngleDeg) {
  float gamma = atan((float) GRABBER_LEN_MM / (float) horizontalDistMM) * RAD_TO_DEG;
  float alpha = 180 - arm1AngleDeg - ARM_1_OFFSET - gamma;

  float a = ARM_2_LEN_MM;
  float b = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));

  return asin(b * sin((float) alpha * DEG_TO_RAD) / a) * RAD_TO_DEG + ARM_2_OFFSET;
}
