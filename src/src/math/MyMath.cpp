#include "MyMath.hpp"

#include <QDebug>

double MyMath::rad(double deg) noexcept { return deg * PI / 180.; }

bool MyMath::collinear(const Point3D &a, const Point3D &b, const Point3D &c) {
  float abx = b.get_x() - a.get_x();
  float aby = b.get_y() - a.get_y();
  float abz = b.get_z() - a.get_z();

  float acx = c.get_x() - a.get_x();
  float acy = c.get_y() - a.get_y();
  float acz = c.get_z() - a.get_z();

  float crossX = aby * acz - abz * acy;
  float crossY = abz * acx - abx * acz;
  float crossZ = abx * acy - aby * acx;

  return (crossX == 0 && crossY == 0 && crossZ == 0);
}
