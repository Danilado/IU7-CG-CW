#include "House.hpp"

namespace {
const Color wallColor(88, 57, 39);
const Color roofColor(128, 0, 0);
} // namespace

House::House(double side) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces();
}

void House::createFaces() {
  const TranslationMatrix t1(0, -side, 0);

  Point3D p1(0, 0, 0);
  Point3D p2(side, 0, 0);
  Point3D p3(side, side, 0);
  Point3D p4(0, side, 0);
  Point3D p5(0, 0, side);
  Point3D p6(side, 0, side);
  Point3D p7(side, side, side);
  Point3D p8(0, side, side);

  {
    faces.push_back(Face(t1 * p1, t1 * p3, t1 * p2)); // front
    faces.back().setColor(wallColor);
    faces.push_back(Face(t1 * p1, t1 * p4, t1 * p3)); // front
    faces.back().setColor(wallColor);
  }

  {
    faces.push_back(Face(t1 * p5, t1 * p6, t1 * p7)); // back
    faces.back().setColor(wallColor);
    faces.push_back(Face(t1 * p5, t1 * p7, t1 * p8)); // back
    faces.back().setColor(wallColor);
  }

  {
    faces.push_back(Face(t1 * p1, t1 * p2, t1 * p6)); // top
    faces.back().setColor(wallColor);
    faces.push_back(Face(t1 * p1, t1 * p6, t1 * p5)); // top
    faces.back().setColor(wallColor);
  }

  {
    faces.push_back(Face(t1 * p4, t1 * p7, t1 * p3)); // bottom
    faces.back().setColor(wallColor);
    faces.push_back(Face(t1 * p4, t1 * p8, t1 * p7)); // bottom
    faces.back().setColor(wallColor);
  }

  {
    faces.push_back(Face(t1 * p1, t1 * p8, t1 * p4)); // left
    faces.back().setColor(wallColor);
    faces.push_back(Face(t1 * p1, t1 * p5, t1 * p8)); // left
    faces.back().setColor(wallColor);
  }

  {
    faces.push_back(Face(t1 * p2, t1 * p3, t1 * p7)); // right
    faces.back().setColor(wallColor);
    faces.push_back(Face(t1 * p2, t1 * p7, t1 * p6)); // right
    faces.back().setColor(wallColor);
  }

  {
    Point3D p1(0, 0, 0);
    Point3D p2(side / 2, -side / 2, 0);
    Point3D p6(side / 2, -side / 2, side);
    Point3D p5(0, 0, side);

    faces.push_back(Face(t1 * p1, t1 * p2, t1 * p6)); // roof left
    faces.back().setColor(roofColor);
    faces.push_back(Face(t1 * p1, t1 * p6, t1 * p5)); // roof left
    faces.back().setColor(roofColor);
  }

  {
    Point3D p1(side, 0, 0);
    Point3D p2(side / 2, -side / 2, 0);
    Point3D p6(side / 2, -side / 2, side);
    Point3D p5(side, 0, side);

    faces.push_back(Face(t1 * p1, t1 * p6, t1 * p2)); // roof right
    faces.back().setColor(roofColor);
    faces.push_back(Face(t1 * p1, t1 * p5, t1 * p6)); // roof right
    faces.back().setColor(roofColor);
  }

  {
    Point3D p1(0, 0, 0);
    Point3D p2(side / 2, -side / 2, 0);
    Point3D p3(side, 0, 0);

    faces.push_back(Face(t1 * p1, t1 * p3, t1 * p2));
    faces.back().setColor(wallColor);
  }

  {
    Point3D p1(0, 0, side);
    Point3D p2(side / 2, -side / 2, side);
    Point3D p3(side, 0, side);

    faces.push_back(Face(t1 * p1, t1 * p2, t1 * p3));
    faces.back().setColor(wallColor);
  }
}