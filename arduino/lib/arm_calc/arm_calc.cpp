#include <arm_calc.h>
#include <constants.h>
#include <math.h>

/**
 * For sides a, b, c - returns the angle A in degrees.
 */
int cosineLawAngle(float a, float b, float c)
{
  return acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0)) / (2.0 * b * c)) * RAD_TO_DEG;
}

/**
 * For sides b, c and the angle opposite side c (gamma) in degrees - returns the side length a.
 */
int cosineLawSide(float b, float c, float gammaDeg)
{
  return sqrt(pow(b, 2.0) + pow(c, 2.0) - 2.0 * b * c * cos(gammaDeg * DEG_TO_RAD));
}

int calcArm1AngleDeg(float horizontalDistMM)
{
  // gamma \ alpha / theta
  float gamma = atan(GRABBER_LEN_MM / horizontalDistMM) * RAD_TO_DEG;

  // cosine law:
  float a = ARM_2_LEN_MM;
  float b = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));
  float c = ARM_1_LEN_MM;

  float theta = cosineLawAngle(a, b, c);

  return 180 - gamma - theta + ARM_1_OFFSET;
}

int calcArm2AngleDeg(float horizontalDistMM)
{
  float a = ARM_1_LEN_MM;
  float b = ARM_2_LEN_MM;
  float c = sqrt(pow(horizontalDistMM, 2.0) + pow(GRABBER_LEN_MM, 2.0));

  return cosineLawAngle(c, a, b) + ARM_2_OFFSET;
}

/**
 * @brief calculates the arm angle required for a particular lateral distance
 *
 * @param x horizontal distance from the normal of the first arm's point of rotation 
 * @return arm 1 angle in degrees
 */
int calcArm1AngleFromTop(double x)
{
  float h = HEIGHT - GRABBER_LEN_MM;
  float side_a = ARM_1_LEN_MM;
  float side_b = ARM_2_LEN_MM;
  float side_c = sqrt(pow(h, 2.0) + pow(x, 2));
  float angle_b = cosineLawAngle(side_b, side_a, side_c);
  float theta;
  if (x <= 0)
  {
    theta = atan(x / h) * RAD_TO_DEG;
    return 90.0 + theta + angle_b + ARM_1_OFFSET;
  }
  else
  {
    theta = atan(h / x) * RAD_TO_DEG;
    return theta + angle_b + ARM_1_OFFSET;
  }

  // let b - a = theta
  // h + x = A (sin(a) - cos(a)) + B (sin(theta) + cos(theta))
  // h + x - B = A (sin(a) - cos(a))
  // (h + x - B) / A = sin(a) - cos(a)
  // (h + x - B) / A = sin(a) - (1 - sin(a))
  // 0 = sin^2(a) - sin(a) - (h + x - B) / A
  // let y = sin(a)
  // y = 1/2 +/- sqrt(1 + 4(1)((h + x - B) / A))/2
  // int c = sqrt(pow(h, 2.0) + pow(x, 2));
  // if (x <= 0)
  // {
  // }
  // return (0.5 - sqrt(1.0 + 4.0 * (h + x - B) / A) / 2.0) * 1000;
  // asin(0.5 - sqrt(1.0 + 4.0 * (h + x - B) / A) / 2.0) * RAD_TO_DEG;
}

/**
 * @brief calculates the second arm position relative to the first arm. 
 *
 * @param x horizontal distance from the normal of the first arm's point of rotation 
 * @return arm 2 angle in degrees
 */
int calcArm2AngleFromTop(double x)
{
  float h = HEIGHT - GRABBER_LEN_MM;
  float side_a = ARM_1_LEN_MM;
  float side_b = ARM_2_LEN_MM;
  float side_c = sqrt(pow(h, 2.0) + pow(x, 2));
  return cosineLawAngle(side_c, side_b, side_a) + ARM_2_OFFSET;
}
