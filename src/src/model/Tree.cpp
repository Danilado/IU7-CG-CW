#include "Tree.hpp"

#include "Color.hpp"
#include "Cube.hpp"
#include "TransformationMatrix.hpp"

namespace {
const Color stem(101, 67, 33);
const Color leaves(0, 99, 56);

constexpr double min_height = 0.1;
constexpr int layers = 9;
constexpr int triangles = 5;
} // namespace

Tree::Tree(double height) : side(height) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces();
}

void Tree::createFaces() {
  TranslationMatrix t1(-side / 2., -side / 2., -side / 2.);
  TranslationMatrix t2(side / 2., side / 2. - side, side / 2.);
  TranslationMatrix t3(0., -side / 2., 0.);
  TranslationMatrix t4(rand() % static_cast<int>(side / 3.) - side / 6., 0.,
                       rand() % static_cast<int>(side / 3.) - side / 6.);
  ScalingMatrix s1(.1, 1, .1);
  ScalingMatrix s2(.7, .7, .7);
  RotationMatrix r1(0., static_cast<double>(rand() % 90), 0, true);

  Cube c(side);

  // stem
  for (const auto &f : c.getFaces()) {
    auto pts = f.getPoints();

    faces.push_back(Face(t4 * (t2 * (s1 * (t1 * pts[0]))),
                         t4 * (t2 * (s1 * (t1 * pts[1]))),
                         t4 * (t2 * (s1 * (t1 * pts[2])))));
    faces.back().setColor(stem);
  }

  // leaves
  for (const auto &f : c.getFaces()) {
    auto pts = f.getPoints();

    faces.push_back(Face(t4 * (t3 * (t2 * (r1 * (s2 * (t1 * pts[0]))))),
                         t4 * (t3 * (t2 * (r1 * (s2 * (t1 * pts[1]))))),
                         t4 * (t3 * (t2 * (r1 * (s2 * (t1 * pts[2])))))));
    faces.back().setColor(leaves);
  }
}
