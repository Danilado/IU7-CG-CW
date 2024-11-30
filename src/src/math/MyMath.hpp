#ifndef MY_MATH_HPP
#define MY_MATH_HPP

#include "Point3D.hpp"

class MyMath {
public:
  static double rad(double deg) noexcept;
  static const double constexpr PI = 3.14159265359;
  static const double constexpr EPS = 1e-6;
  static bool collinear(const Point3D &a, const Point3D &b, const Point3D &c);
};

#endif
