#pragma once

class Color {
public:
  Color() = default;
  Color(int r, int g, int b) : r(r), g(g), b(b) {};

  int r = 0;
  int g = 0;
  int b = 0;
};
