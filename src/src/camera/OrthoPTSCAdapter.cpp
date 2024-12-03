#include "OrthoPTSCAdapter.hpp"
#include <QDebug>

double OrthoPTSCAdapter::shadyExpFunc(double x) {
  // https://www.desmos.com/calculator/uf7isgsby3
  if (x >= 1)
    return x;

  return exp((x - 1) / 2.71828);
}

std::shared_ptr<Point2D> OrthoPTSCAdapter::convert(const Point3D &pt) {
  // Point3D tmppt = transformPoint(pt);
  double fovl = 1350;
  // double persp_coeff = (fovl / shadyExpFunc(fovl + pt.get_z() - 1350));
  double persp_coeff = (fovl / pt.get_z());
  double resx = persp_coeff * pt.get_x();
  double resy = persp_coeff * pt.get_y();

  return std::make_shared<Point2D>(resx, resy);
  // Point3D tmppt = transformPoint(pt);
  // return std::make_shared<Point2D>(pt.get_x(), pt.get_y());
}
