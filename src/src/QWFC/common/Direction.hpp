#pragma once

#include <tuple>

enum Direction { up, right, down, left, _count };

std::pair<int, int> to_coords(const Direction &dir);
