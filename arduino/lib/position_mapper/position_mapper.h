#ifndef POSITION_MAPPER
#define POSITION_MAPPER

#include <unordered_map>
#include <vector>
#include <string>
#include <array>
#include <initializer_list>

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
  static const std::string ARM_RAISED;
  static const std::string ARM_WAITING;
  static const std::string ARM_RESTING;
  static const std::string OPEN_GRABBER;
  static const std::string CLOSE_GRABBER;

  static PositionMapper *get_instance();
  std::vector<int> positions_from_moves(std::initializer_list<std::string> moves);
  std::vector<int> positions_from_distances(int distances...);
};

#endif
