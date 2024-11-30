#include "OrthogonalCamera.hpp"
#include "MyMath.hpp"

#include <cmath>

OrthogonalCamera::OrthogonalCamera() : BaseCamera() {}

void OrthogonalCamera::accept(BaseVisitor &vis) { vis.visit(*this); }

std::unique_ptr<Object> OrthogonalCamera::clone() const {
  std::unique_ptr<OrthogonalCamera> res = std::make_unique<OrthogonalCamera>();
  res->restoreMemento(this->createMemento());
  return std::move(res);
}

Point3D OrthogonalCamera::getDirection() const {
  auto translation = transform->getNegOffset();
  auto tmp = translation.apply(transform->apply(Point3D(0, 0, 1))).normalize();
  return Point3D(-tmp.get_x(), -tmp.get_y(), tmp.get_z());
}