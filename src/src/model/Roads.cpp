#include "Roads.hpp"
#include "Square.hpp"

namespace {
const ScalingMatrix s1(0.2, 1, 1);
const ScalingMatrix s2(1, 1, 0.5);
const ScalingMatrix s3(0.2, 1, 0.2);
const RotationMatrix r1(0, 90, 0, true);
const RotationMatrix r2(0, -90, 0, true);
} // namespace

CrossRoad::CrossRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void CrossRoad::createFaces(Color color) {
  Square sq1(side, color);

  {
    const TranslationMatrix t1(-side / 2, 0, 0);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    const TranslationMatrix t3(-side / 2, 0, 0);

    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(
          Face(t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
               t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
               t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
      faces.back().setColor(color);
    }
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(
          Face(t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
               t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
               t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
      faces.back().setColor(color);
    }
  }
  {
    const TranslationMatrix t1(-side / 2, 0, 0);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    const TranslationMatrix t3(0, 0, -side / 2);

    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s2.apply(s1.apply(t1.apply(pts[0])))),
                           t2.apply(s2.apply(s1.apply(t1.apply(pts[1])))),
                           t2.apply(s2.apply(s1.apply(t1.apply(pts[2]))))));
      faces.back().setColor(color);
    }
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(
          Face(t2.apply(t3.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
               t2.apply(t3.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
               t2.apply(t3.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
      faces.back().setColor(color);
    }
  }
  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}

HorizontalRoad::HorizontalRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void HorizontalRoad::createFaces(Color color) {
  const TranslationMatrix t1(-side / 2, 0, 0);
  const TranslationMatrix t2(side / 2, 0, side / 2);
  const TranslationMatrix t3(-side / 2, 0, 0);

  Square sq1(side, color);

  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }
  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }

  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}

VerticalRoad::VerticalRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void VerticalRoad::createFaces(Color color) {
  const TranslationMatrix t1(-side / 2, 0, 0);
  const TranslationMatrix t2(side / 2, 0, side / 2);
  const TranslationMatrix t3(0, 0, -side / 2);

  Square sq1(side, color);

  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(Face(t2.apply(s2.apply(s1.apply(t1.apply(pts[0])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[1])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[2]))))));
    faces.back().setColor(color);
  }
  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(t3.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(t3.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(t3.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }

  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}

BRRoad::BRRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void BRRoad::createFaces(Color color) {
  const TranslationMatrix t1(-side / 2, 0, 0);
  const TranslationMatrix t2(side / 2, 0, side / 2);

  Square sq1(side, color);

  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(Face(t2.apply(s2.apply(s1.apply(t1.apply(pts[0])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[1])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[2]))))));
    faces.back().setColor(color);
  }
  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }
  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}

TRRoad::TRRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void TRRoad::createFaces(Color color) {
  const TranslationMatrix t1(-side / 2, 0, -side);
  const TranslationMatrix t2(side / 2, 0, side / 2);

  Square sq1(side, color);

  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(Face(t2.apply(s2.apply(s1.apply(t1.apply(pts[0])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[1])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[2]))))));
    faces.back().setColor(color);
  }
  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }
  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}

LBRoad::LBRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void LBRoad::createFaces(Color color) {
  const TranslationMatrix t1(-side / 2, 0, 0);
  const TranslationMatrix t2(side / 2, 0, side / 2);

  Square sq1(side, color);

  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(Face(t2.apply(s2.apply(s1.apply(t1.apply(pts[0])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[1])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[2]))))));
    faces.back().setColor(color);
  }
  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(r2.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }
  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}

TLRoad::TLRoad(double side, Color color) : side(side) {
  if (side <= 0) {
    throw std::invalid_argument("Side length must be greater than zero.");
  }
  createFaces(color);
}

void TLRoad::createFaces(Color color) {
  const TranslationMatrix t1(-side / 2, 0, -side);
  const TranslationMatrix t2(side / 2, 0, side / 2);

  Square sq1(side, color);

  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(Face(t2.apply(s2.apply(s1.apply(t1.apply(pts[0])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[1])))),
                         t2.apply(s2.apply(s1.apply(t1.apply(pts[2]))))));
    faces.back().setColor(color);
  }
  for (auto &face : sq1.getFaces()) {
    auto pts = face.getPoints();
    faces.push_back(
        Face(t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[0]))))),
             t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[1]))))),
             t2.apply(r1.apply(s2.apply(s1.apply(t1.apply(pts[2])))))));
    faces.back().setColor(color);
  }
  {
    const TranslationMatrix t1(-side / 2, 0, -side / 2);
    const TranslationMatrix t2(side / 2, 0, side / 2);
    for (auto &face : sq1.getFaces()) {
      auto pts = face.getPoints();
      faces.push_back(Face(t2.apply(s3.apply(t1.apply(pts[0]))),
                           t2.apply(s3.apply(t1.apply(pts[1]))),
                           t2.apply(s3.apply(t1.apply(pts[2])))));
      faces.back().setColor(color);
    }
  }
}
