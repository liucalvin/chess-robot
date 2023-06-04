#include <arm_calc.h>
#include <constants.h>
#include <unity.h>

constexpr int DELTA = 5;

void setUp(void) {
    // unused
}

void tearDown(void) {
    // unused
}

void arm_angle_test_1() {
  int distance = 100;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance, arm1AngleDeg);

  TEST_ASSERT_INT_WITHIN(DELTA, 68 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 36 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_2() {
  int distance = 160;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance, arm1AngleDeg);

  TEST_ASSERT_INT_WITHIN(DELTA, 85 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 49 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_3() {
  int distance = 250;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance, arm1AngleDeg);

  TEST_ASSERT_INT_WITHIN(DELTA, 106 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 72 + ARM_2_OFFSET, arm2AngleDeg);
}

void arm_angle_test_4() {
  int distance = 20;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance, arm1AngleDeg);

  TEST_ASSERT_INT_WITHIN(DELTA, 29 + ARM_1_OFFSET, arm1AngleDeg);
  TEST_ASSERT_INT_WITHIN(DELTA, 25 + ARM_2_OFFSET, arm2AngleDeg);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(arm_angle_test_1); 
    RUN_TEST(arm_angle_test_2); 
    RUN_TEST(arm_angle_test_3); 
    RUN_TEST(arm_angle_test_4); 
    UNITY_END();

    return 0;
}