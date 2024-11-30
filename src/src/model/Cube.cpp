#include "Cube.hpp"

Cube::Cube(double side) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces();
}

void Cube::createFaces() {
  Point3D p1(0, 0, 0);
  Point3D p2(side, 0, 0);
  Point3D p3(side, side, 0);
  Point3D p4(0, side, 0);
  Point3D p5(0, 0, side);
  Point3D p6(side, 0, side);
  Point3D p7(side, side, side);
  Point3D p8(0, side, side);

  faces.push_back(Face(Plane(p1, p3, p2), {p1, p2, p3, p4})); // front
  faces.back().setColor(Color(255, 0, 0));
  faces.push_back(Face(Plane(p5, p6, p7), {p5, p8, p7, p6})); // back
  faces.back().setColor(Color(0, 255, 0));
  faces.push_back(Face(Plane(p1, p2, p6), {p1, p5, p6, p2})); // top
  faces.back().setColor(Color(255, 255, 0));
  faces.push_back(Face(Plane(p4, p7, p3), {p4, p3, p7, p8})); // bottom
  faces.back().setColor(Color(0, 255, 255));
  faces.push_back(Face(Plane(p1, p8, p4), {p1, p5, p8, p4})); // left
  faces.back().setColor(Color(0, 0, 255));
  faces.push_back(Face(Plane(p2, p3, p7), {p2, p6, p7, p3})); // right
  faces.back().setColor(Color(255, 0, 255));
}
