#pragma once

#include "MyMath.hpp"
#include "Point3D.hpp"

class Plane {
public:
  Plane(const Point3D &point1, const Point3D &point2, const Point3D &point3);
  const Point3D &getNormal() const { return normal; }

  bool containsPoint(const Point3D &point) const;
  const Point3D &getP1() const { return p1; }
  const Point3D &getP2() const { return p2; }
  const Point3D &getP3() const { return p3; }

protected:
  Point3D p1, p2, p3;
  Point3D normal;
};
