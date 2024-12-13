#include "Square.hpp"

Square::Square(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void Square::createFaces(Color color) {
  Point3D p1(0, 0, 0);
  Point3D p2(side, 0, 0);
  Point3D p5(0, 0, side);
  Point3D p6(side, 0, side);

  faces.push_back(Face(p1, p2, p6)); // top
  faces.back().setColor(color);
  faces.push_back(Face(p1, p6, p5)); // top
  faces.back().setColor(color);
}
