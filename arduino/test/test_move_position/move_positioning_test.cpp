#include <unity.h>
#include <utils.h>
#include <string>

#include <position_mapper.h>

void setUp(void)
{
  // unused
}

void tearDown(void)
{
  // unused
}

void test_move_order()
{
  //  {"f1", {201, 1282, 814}},
  //  {"f1a", {201, 1022, 814}},
  //  {"f2", {351, 1152, 824}},
  //  {ARM_WAITING, {1201, 502, 804}},
  PositionMapper *mapper = PositionMapper::get_instance();
  std::vector<int> positions = mapper->get_motor_positions_from_move("f1", "f2");
  // 4 movements (* 2 positions each) and 2 grabber toggles
  TEST_ASSERT_EQUAL(10, positions.size());
  TEST_ASSERT_EQUAL(201286, positions[0]);
  TEST_ASSERT_EQUAL(814, positions[1]);
  TEST_ASSERT_EQUAL(3, positions[2]);
  TEST_ASSERT_EQUAL(506, positions[3]);
  TEST_ASSERT_EQUAL(1200506, positions[8]);
  TEST_ASSERT_EQUAL(804, positions[9]);
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_move_order);
  UNITY_END();

  return 0;
}