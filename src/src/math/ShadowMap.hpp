#pragma once

#include "TransformationMatrix.hpp"
#include <QDebug>
#include <limits>
#include <vector>

class ShadowMap {
  TransformationMatrix view;
  std::pair<double, double> coeffs;
  std::vector<std::vector<double>> depth;

  double min_z, max_z;
  double offset_x;
  double offset_y;

public:
  ShadowMap(TransformationMatrix &&matrix, std::pair<double, double> coeffs,
            double ox, double oy, std::vector<std::vector<double>> &&d)
      : view(matrix), coeffs(coeffs), depth(d), offset_x(ox), offset_y(oy) {
    if (depth.empty() || depth.front().empty())
      return;

    min_z = std::numeric_limits<double>::infinity();
    max_z = -std::numeric_limits<double>::infinity();
    for (const auto &row : depth)
      for (const double &val : row) {
        if (std::isinf(val))
          continue;
        min_z = std::min(min_z, val);
        max_z = std::max(max_z, val);
      }
    qDebug() << "Shadowmap props: " << min_z << " " << max_z;
  };

  bool isValid() const { return !(depth.empty() || depth.front().empty()); }

  double getBrightness(const Point3D &pt);
};