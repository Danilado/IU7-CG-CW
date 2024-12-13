#include "OrthoPTSCAdapter.hpp"
#include "MyMath.hpp"
#include <QDebug>

std::shared_ptr<Point2D> OrthoPTSCAdapter::convert(const Point3D &pt) {
  // return std::make_shared<Point2D>(pt.get_x(), pt.get_y());

  double fovl = 1000;
  double aspect_ratio = 1404. / 977.;
  double z = std::max(2 * MyMath::EPS, pt.get_z()); // Костыль (:
  double persp_coeff = fovl / (z * aspect_ratio);
  double resx = persp_coeff * pt.get_x();
  double resy = persp_coeff * pt.get_y();

  return std::make_shared<Point2D>(resx, resy);
}
