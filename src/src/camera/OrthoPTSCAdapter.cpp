#include "OrthoPTSCAdapter.hpp"
#include "MyMath.hpp"
#include <QDebug>

std::shared_ptr<Point2D> OrthoPTSCAdapter::convert(const Point3D &pt) {
  double fovl = 1350;
  double z = std::max(2 * MyMath::EPS, pt.get_z()); // Костыль (:
  double persp_coeff = (fovl / z);
  double resx = persp_coeff * pt.get_x();
  double resy = persp_coeff * pt.get_y();

  return std::make_shared<Point2D>(resx, resy);
}
