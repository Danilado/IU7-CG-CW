#include "ShadowMap.hpp"
#include "MyMath.hpp"
#include <cmath>

namespace {
double invlerp(double min, double max, double val) {
  return (val - min) / (max - min);
}
} // namespace

double ShadowMap::getBrightness(const Point3D &pt) const {
  if (depth.empty() || depth.front().empty()) {
    return 0.;
  }

  auto tmppt = view.apply(pt);
  int x = std::floor((tmppt.get_x() - offset_x) * coeffs.first);
  int y = std::floor((tmppt.get_y() - offset_y) * coeffs.second);

  if (x < 0 || x >= depth.front().size() || y < 0 || y >= depth.size()) {
    return 0.;
  }

  if (tmppt.get_z() <= depth[y][x] + std::abs(2. / coeffs.first) +
                           std::abs(2. / coeffs.second)) {
    return 1.;

    double val = 0.4 + (0.6 - 0.6 * invlerp(min_z, max_z, tmppt.get_z()));
    if (std::isnan(val) || std::isinf(val))
      val = 1.;
    val = std::clamp(val, 0.4, 1.);
    return val;
  }

  return 0.4;
}
