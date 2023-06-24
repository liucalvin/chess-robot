#include <unity.h>
#include <utils.h>
#include <string>
#include <utils.h>

void setUp(void)
{
  // unused
}

void tearDown(void)
{
  // unused
}

void verify_is_number()
{
  std::string input = "1234";
  bool is_input_number = is_valid_number(input);

  TEST_ASSERT_TRUE(is_input_number);
}

void verify_is_not_number()
{
  std::string input = "7f4";
  bool is_input_number = is_valid_number(input);

  TEST_ASSERT_FALSE(is_input_number);
}

void test_trim_whitespace()
{
  std::string input = "  12 34   ";
  trim_whitespace(input);
  TEST_ASSERT_TRUE("1234" == input);
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(verify_is_number);
  RUN_TEST(verify_is_not_number);
  RUN_TEST(test_trim_whitespace);
  UNITY_END();

  return 0;
}