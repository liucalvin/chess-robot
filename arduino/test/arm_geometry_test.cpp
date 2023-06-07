#include <arm_calc.h>
#include <constants.h>
#include <unity.h>

constexpr int DELTA = 2;

void setUp(void) {
    // unused
}

void tearDown(void) {
    // unused
}

void arm_angle_test_1() {
  int distance = 100;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 65 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 38 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_2() {
  int distance = 160;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 83 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 50 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_3() {
  int distance = 250;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 105 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 74 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_4() {
  int distance = 20;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 29 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 25 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_5() {
  int distance = 300;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance);

  TEST_ASSERT_INT_WITHIN(DELTA, 116 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 89 + ARM_2_OFFSET, arm2AngleDeg);

  // gamma = 19
  // theta = 44

  // alpha = 45
  // b = 318
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(arm_angle_test_1); 
    RUN_TEST(arm_angle_test_2); 
    RUN_TEST(arm_angle_test_3); 
    RUN_TEST(arm_angle_test_4); 
    RUN_TEST(arm_angle_test_5); 
    UNITY_END();

    return 0;
}