#include "Plane.hpp"
#include <stdexcept>

Plane::Plane(const Point3D &point1, const Point3D &point2,
             const Point3D &point3)
    : p1(point1), p2(point2), p3(point3) {
  double abx = point2.get_x() - point1.get_x();
  double aby = point2.get_y() - point1.get_y();
  double abz = point2.get_z() - point1.get_z();

  double acx = point3.get_x() - point1.get_x();
  double acy = point3.get_y() - point1.get_y();
  double acz = point3.get_z() - point1.get_z();

  double normalX = aby * acz - abz * acy;
  double normalY = abz * acx - abx * acz;
  double normalZ = abx * acy - aby * acx;

  if (std::abs(normalX) < MyMath::EPS && std::abs(normalY) < MyMath::EPS &&
      std::abs(normalZ) < MyMath::EPS)
    throw std::invalid_argument(
        "Points are collinear and do not define a plane.");

  normal = Point3D(normalX, normalY, normalZ);
}

bool Plane::containsPoint(const Point3D &point) const {
  float dx = point.get_x() - p1.get_x();
  float dy = point.get_y() - p1.get_y();
  float dz = point.get_z() - p1.get_z();

  float distance =
      normal.get_x() * dx + normal.get_y() * dy + normal.get_z() * dz;

  return std::abs(distance) < MyMath::EPS;
}