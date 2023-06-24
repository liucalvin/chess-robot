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
  PositionMapper *mapper = PositionMapper::getInstance();
  std::vector<int> positions = mapper->get_motor_positions_from_move("f1", "f2");
  // 3 movements (* 3 positions each) and 2 grabber toggles
  TEST_ASSERT_EQUAL(11, positions.size());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_move_order);
  UNITY_END();

  return 0;
}