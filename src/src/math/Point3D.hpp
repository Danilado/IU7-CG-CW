#ifndef POINT_3D_HPP
#define POINT_3D_HPP

#include "Point2D.hpp"

class Point3D : public Point2D {
public:
  double z;

public:
  Point3D() = default;
  Point3D(double x, double y, double z) noexcept : Point2D(x, y), z(z) {}
  Point3D(const Point2D &pt);
  Point3D(Point2D &&pt);
  ~Point3D() = default;

  double get_z() const noexcept;
  void set_z(double n) noexcept;

  Point3D operator*(const double &val) const;
  Point3D operator/(const double &val) const;
  Point3D operator+(const Point3D &other) const;
  Point3D operator-(const Point3D &other) const;
  Point3D operator-() const;
  Point3D normalize() const;
  Point3D operator%(const Point3D &other) const;

  Point3D &operator=(const Point3D &other);
  Point3D &operator+=(const Point3D &other);

  void debug() const;

  double operator*(const Point3D &other) const;

  static Point3D average(const Point3D &p1, const Point3D &p2,
                         const Point3D &p3);
};

#endif
