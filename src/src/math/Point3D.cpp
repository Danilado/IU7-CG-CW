#include "Point3D.hpp"
#include <QDebug>
#include <cmath>

Point3D::Point3D(const Point2D &pt) : Point2D(pt), z(0.) {}
Point3D::Point3D(Point2D &&pt) : Point2D(pt), z(0.) {}

double Point3D::get_z() const noexcept { return z; }
void Point3D::set_z(double n) noexcept { z = n; }

Point3D Point3D::operator-() const { return Point3D(-x, -y, -z); }

Point3D Point3D::normalize() const {
  double length = std::sqrt(x * x + y * y + z * z);
  return Point3D(x / length, y / length, z / length);
}

double Point3D::operator*(const Point3D &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Point3D Point3D::operator+(const Point3D &other) const {
  return Point3D(x + other.x, y + other.y, z + other.z);
}

Point3D Point3D::operator%(const Point3D &other) const {
  return Point3D(y * other.z - z * other.y, z * other.x - x * other.z,
                 x * other.y - y * other.x);
}

Point3D &Point3D::operator+=(const Point3D &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Point3D Point3D::operator-(const Point3D &other) const {
  return Point3D(x - other.x, y - other.y, z - other.z);
}

Point3D Point3D::operator*(const double &val) const {
  return Point3D(x * val, y * val, z * val);
}

void Point3D::debug() { qDebug() << x << " " << y << " " << z; }
