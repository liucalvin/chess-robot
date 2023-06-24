#include <string>
#include <array>
#include <vector>

#include <position_mapper.h>

static const std::string ARM_RAISED = "raised";
static const std::string ARM_WAITING = "waiting";
static const std::string ARM_RESTING = "rest";
static const int TOGGLE_GRABBER_INSTRUCTION = 3;
static const int POSITION_DIMENSIONALITY = 3;

PositionMapper *PositionMapper::instance = nullptr;

PositionMapper::PositionMapper()
{
}

PositionMapper *PositionMapper::getInstance()
{
  if (instance == nullptr)
  {
    instance = new PositionMapper();
  }

  return instance;
}

static std::unordered_map<std::string, std::array<int, POSITION_DIMENSIONALITY>> move_mappings{
    {ARM_RAISED, {901, 502, 804}},
    {ARM_WAITING, {201, 1302, 804}},
    {ARM_RESTING, {901, 1262, 804}},
    {"f1", {201, 1302, 804}},
    {"f2", {401, 1152, 804}},
    {"f3", {581, 1102, 804}}};

std::vector<int> PositionMapper::get_motor_positions_from_move(std::string from, std::string to)
{
  std::vector<int> instructions;

  if (move_mappings.count(from) > 0)
  {
    add_positions(from, instructions);
    instructions.push_back(TOGGLE_GRABBER_INSTRUCTION);
    add_positions(ARM_RAISED, instructions);
    add_positions(to, instructions);
    instructions.push_back(TOGGLE_GRABBER_INSTRUCTION);
  }
  return instructions;
}

void PositionMapper::add_positions(std::string move, std::vector<int> &instructions)
{
  std::array<int, POSITION_DIMENSIONALITY> &motor_positions = move_mappings[move];

  for (size_t i = 0; i < motor_positions.size(); ++i)
  {
    int value = motor_positions[i];
    instructions.push_back(value);
  }
}
