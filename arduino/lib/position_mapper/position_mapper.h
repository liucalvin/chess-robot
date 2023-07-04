#ifndef POSITION_MAPPER
#define POSITION_MAPPER

#include <unordered_map>
#include <vector>
#include <string>
#include <array>

/**
 * @brief A singleton class wrapping all functionality that maps 
 *        chess positions to the arm's motor rotational positions. 
 * 
 */
class PositionMapper
{
private:
  static PositionMapper *instance;
  void add_positions(std::string move, std::vector<int> &instructions);
  PositionMapper();
  PositionMapper(const PositionMapper &obj) = delete;
  PositionMapper &operator=(const PositionMapper &) = delete;

public:
  static PositionMapper *get_instance();
  std::vector<int> get_motor_positions_from_move(std::string from, std::string to);
};

#endif
