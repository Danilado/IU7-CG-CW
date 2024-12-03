#pragma once
#include <QDebug>

class Color {
public:
  Color() = default;
  Color(int r, int g, int b) : r(r), g(g), b(b) {};

  int r = 0;
  int g = 0;
  int b = 0;

  Color operator*(double val) const {
    Color res(static_cast<int>(r * val), static_cast<int>(g * val),
              static_cast<int>(b * val));
    if (res.r < 0 || res.r > 255 || res.g < 0 || res.g > 255 || res.b < 0 ||
        res.b > 255) {
      qDebug() << val;
      qDebug() << res.r << res.g << res.b;
      throw "ZHOPA";
    }
    return res;
  }
};
