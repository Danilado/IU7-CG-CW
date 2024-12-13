#include "Face.hpp"
#include "MyMath.hpp"

#include <ranges>

bool Face::isVisible(const Point3D &camPosition,
                     const TransformationMatrix &transf) const {
  auto camDirection = transf.apply(tr.getP1()) - camPosition;
  if (std::abs(camDirection.get_x()) <= MyMath::EPS &&
      std::abs(camDirection.get_y()) <= MyMath::EPS &&
      std::abs(camDirection.get_z()) <= MyMath::EPS)
    camDirection = transf.apply(tr.getP2()) - camPosition;

  auto newnorm = transf.getNegOffset().apply(transf.apply(tr.getNormal()));

  return newnorm.normalize() * camDirection.normalize() < 0;
}