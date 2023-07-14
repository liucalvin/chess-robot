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

void test_order_from_moves()
{
  //  {"f1", {201, 1282, 814}},
  //  {"f1a", {201, 1022, 814}},
  //  {"f2", {351, 1152, 824}},
  //  {ARM_WAITING, {1201, 502, 804}},
  PositionMapper *mapper = PositionMapper::get_instance();
  std::vector<int> positions = mapper->positions_from_moves({
      PositionMapper::OPEN_GRABBER,
      "f1",
      PositionMapper::CLOSE_GRABBER,
      "f2",
      PositionMapper::OPEN_GRABBER,
  });
  // 2 movements (* 2 positions each), 3 grabber, 1 RAISED, 1 WAITING
  TEST_ASSERT_EQUAL(10, positions.size());
  // open, f1 arm 1+2, f1 rotator, close, RAISED, f2 arm 1+2, f2 rotator, open, WAITING
  std::vector<int> expected = {
      03,      // open
      201286,  // f1 arm 1+2 (20, 128)
      814,     // f1 rotator
      13,      // close
      502,     // raised
      351156,  // f2 arm 1+2 (35, 115)
      824,     // f2 rotator
      03,      // open
      1200506, // WAITING arm 1+2 (120, 50)
      804      // WAITING rotator
  };
  for (size_t i = 0; i < positions.size(); i++)
  {
    TEST_ASSERT_EQUAL(expected[i], positions[i]);
  }
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_order_from_moves);
  UNITY_END();

  return 0;
}