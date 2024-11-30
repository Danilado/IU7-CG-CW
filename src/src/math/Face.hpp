#pragma once

#include "Color.hpp"
#include "Plane.hpp"
#include "TransformationMatrix.hpp"
#include <stdexcept>
#include <vector>

class Face {
public:
  Face(const Plane &p, const std::vector<Point3D> &points)
      : plane(p), vertices(points) {
    if (vertices.size() < 3) {
      throw std::invalid_argument("A face must have at least three vertices.");
    }
  }

  Point3D getNormal() const { return plane.getNormal(); }
  const std::vector<Point3D> &getPoints() const { return vertices; }
  bool isVisible(const Point3D &camPosition,
                 const TransformationMatrix &transf) const;

  void setColor(const Color &col) { c = col; };
  const Color &getColor() const { return c; }

private:
  Plane plane;
  std::vector<Point3D> vertices;
  Color c = {0, 0, 0};
};