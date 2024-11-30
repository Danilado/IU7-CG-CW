#include "Face.hpp"
#include "MyMath.hpp"

bool Face::isVisible(const Point3D &camPosition,
                     const TransformationMatrix &transf) const {
  auto camDirection = transf.apply(plane.getP1()) - camPosition;
  if (std::abs(camDirection.get_x()) <= MyMath::EPS &&
      std::abs(camDirection.get_y()) <= MyMath::EPS &&
      std::abs(camDirection.get_z()) <= MyMath::EPS)
    camDirection = transf.apply(plane.getP2()) - camPosition;

  auto newnorm = transf.getNegOffset().apply(transf.apply(plane.getNormal()));

  return newnorm.normalize() * camDirection.normalize() <= MyMath::EPS;
}