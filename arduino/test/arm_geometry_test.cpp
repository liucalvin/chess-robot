#include <arm_calc.h>
#include <unity.h>

void setUp(void) {
    // unused
}

void tearDown(void) {
    // unused
}

void arm_angle_test() {
  int distance = 100;
  int arm1AngleDeg = calcArm1AngleDeg(distance);
  int arm2AngleDeg = calcArm2AngleDeg(distance, arm1AngleDeg);

  TEST_ASSERT_EQUAL(66, arm1AngleDeg);
  TEST_ASSERT_EQUAL(44, arm2AngleDeg);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(arm_angle_test); 
    UNITY_END();

    return 0;
}