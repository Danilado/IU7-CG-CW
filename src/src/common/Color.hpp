#pragma once

class Color {
public:
  Color() = default;
  Color(int r, int g, int b) : r(r), g(g), b(b) {};

  int r = 0;
  int g = 0;
  int b = 0;

  Color operator*(double val) const {
    return Color(static_cast<int>(r * val), static_cast<int>(g * val),
                 static_cast<int>(b * val));
  }
};
