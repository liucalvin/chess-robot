#include <string>
#include <cctype>
#include <algorithm>

#include <utils.h>

bool is_valid_number(std::string input)
{
  trim_whitespace(input);
  for (uint8_t i = 0; i < input.length(); i++)
  {
    if (!std::isdigit(input.at(i)))
    {
      return false;
    }
  }
  return true;
}

void trim_whitespace(std::string &input)
{
  input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
}
