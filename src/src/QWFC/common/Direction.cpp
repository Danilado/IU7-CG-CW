#include "Direction.hpp"

std::pair<int, int> to_coords(const Direction &dir) {
  switch (dir) {
  case up:
    return {0, -1};
    break;
  case right:
    return {1, 0};
    break;
  case down:
    return {0, 1};
    break;
  case left:
    return {-1, 0};
    break;
  default:
    break;
  }

  return {};
}