#include <arm_calc.h>
#include <constants.h>
#include <unity.h>

constexpr int DELTA = 2;

void setUp(void)
{
  // unused
}

void tearDown(void)
{
  // unused
}

void arm_angle_test_1()
{
  int distance = 100;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 65 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 38 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_2()
{
  int distance = 160;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 83 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 50 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_3()
{
  int distance = 250;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 105 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 74 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_4()
{
  int distance = 300;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 116 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 89 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_5()
{
  int distance = 400;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 141 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 132 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_max_distance_angle_test()
{
  int distance = 440;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 162 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 172 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_min_distance_angle_test()
{
  int distance = 0;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 18 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 27 + ARM_2_OFFSET, arm2AngleDeg);
}

void top_arm_angle_test_1()
{
  int distance = 0;
  int arm1AngleDeg = calcArm1AngleFromTop(distance);
  int arm2AngleDeg = calcArm2AngleFromTop(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 59, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 115, arm2AngleDeg);
}


void top_arm_angle_test_2()
{
  int distance = 50;
  int arm1AngleDeg = calcArm1AngleFromTop(distance);
  int arm2AngleDeg = calcArm2AngleFromTop(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 67, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 116, arm2AngleDeg);
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  // RUN_TEST(arm_angle_test_1);
  // RUN_TEST(arm_angle_test_2);
  // RUN_TEST(arm_angle_test_3);
  // RUN_TEST(arm_angle_test_4);
  // RUN_TEST(arm_angle_test_5);
  // RUN_TEST(arm_max_distance_angle_test);
  // RUN_TEST(arm_min_distance_angle_test);
  RUN_TEST(top_arm_angle_test_1);
  RUN_TEST(top_arm_angle_test_2);
  UNITY_END();

  return 0;
}