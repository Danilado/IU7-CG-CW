#ifndef ORTHOGONAL_PTSC_ADAPTER_HPP
#define ORTHOGONAL_PTSC_ADAPTER_HPP

#include "BasePTSCAdapter.hpp"
#include "TransformationMatrix.hpp"

class OrthoPTSCAdapter : public BasePTSCAdapter {
private:
  static double shadyExpFunc(double x);
  TransformationMatrix mat;

public:
  std::shared_ptr<Point2D> convert(const Point3D &pt) override;
};

#endif
