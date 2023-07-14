#include <string>
#include <array>
#include <vector>
#include <cstdarg>
#include <initializer_list>

#include <constants.h>
#include <arm_calc.h>
#include <position_mapper.h>

static const int OPEN_GRABBER_INSTRUCTION = 03;
static const int CLOSE_GRABBER_INSTRUCTION = 13;
static const int TOGGLE_GRABBER_INSTRUCTION = 3;
static const int ARM_RAISED_INSTRUCTION = 502;
static const int POSITION_DIMENSIONALITY = 3;

const std::string PositionMapper::ARM_RAISED = "raised";
const std::string PositionMapper::ARM_WAITING = "waiting";
const std::string PositionMapper::ARM_RESTING = "rest";
const std::string PositionMapper::OPEN_GRABBER = "open";
const std::string PositionMapper::CLOSE_GRABBER = "close";

PositionMapper *PositionMapper::instance = nullptr;

PositionMapper::PositionMapper()
{
}

PositionMapper *PositionMapper::get_instance()
{
  if (instance == nullptr)
  {
    instance = new PositionMapper();
  }

  return instance;
}

/**
 * @brief Map of all the arm's motor positions to positions on the board.
 *        For each position on the board there is a mapping to the position
 *        directly above the position (e.g. e1 and e1a), which is used
 *        when setting pieces down so that they don't knock over others.
 *
 *        Each position is specified by (up to) three numbers, with the
 *        specific motor encoded by the last digit.
 */
static std::unordered_map<std::string, std::array<int, POSITION_DIMENSIONALITY>> move_mappings{
    {PositionMapper::ARM_WAITING, {1201, 502, 804}},
    {PositionMapper::ARM_RESTING, {901, 1262, 804}},
    {"f1", {201, 1282, 814}},
    {"f1a", {201, 1022, 814}},
    {"f2", {351, 1152, 824}},
    {"f2a", {351, 902, 824}},
    {"f3", {541, 1082, 824}},
    {"f3a", {541, 882, 824}},
    {"f4", {681, 1032, 824}},
    {"f4a", {681, 802, 824}},
    {"f5", {841, 982, 884}},
    {"f5a", {901, 782, 884}},
    {"", {1, 2, 4}},
    {"", {1, 2, 4}}};

std::vector<int> PositionMapper::positions_from_moves(std::initializer_list<std::string> moves)
{
  std::vector<int> instructions;
  for (const std::string &move : moves)
  {
    add_positions(move, instructions);
  }

  add_positions(ARM_WAITING, instructions);

  return instructions;
}

std::vector<int> PositionMapper::positions_from_distances(int distances...)
{
  std::vector<int> instructions;
  va_list args;
  va_start(args, distances);

  for (int i = 0; i < distances; ++i)
  {
    int dist = va_arg(args, int);

    int arm1AngleDeg = calcArm1AngleFromTop(dist);
    int arm2AngleDeg = calcArm2AngleFromTop(dist);
    int combined = arm1AngleDeg * 10000 + arm2AngleDeg * 10 + MOVE_IN_PARALLEL_ID;
    instructions.push_back(combined);
    instructions.push_back(TOGGLE_GRABBER_INSTRUCTION);
    add_positions(ARM_RAISED, instructions);
  }

  add_positions(ARM_WAITING, instructions);

  va_end(args);
  return instructions;
}

/**
 * @brief adds the motor positions for the specified move, with arms 1 and 2
 *        moving in parallel and the rotator as a separate movement.
 *
 * @param move the move in chess notation (e.g. e5)
 * @param instructions
 */
void PositionMapper::add_positions(std::string move, std::vector<int> &instructions)
{
  if (move == CLOSE_GRABBER)
  {
    instructions.push_back(CLOSE_GRABBER_INSTRUCTION);
    add_positions(ARM_RAISED, instructions);
  }
  else if (move == OPEN_GRABBER)
  {
    instructions.push_back(OPEN_GRABBER_INSTRUCTION);
  }
  else if (move == ARM_RAISED)
  {
    instructions.push_back(ARM_RAISED_INSTRUCTION);
  }
  else
  {
    if (move_mappings.count(move) > 0)
    {
      std::array<int, POSITION_DIMENSIONALITY> &motor_positions = move_mappings[move];

      int first = motor_positions[0] / 10;
      int second = motor_positions[1] / 10;
      int combined = first * 10000 + second * 10 + MOVE_IN_PARALLEL_ID;
      instructions.push_back(combined);

      instructions.push_back(motor_positions[2]);
    }
  }
}
