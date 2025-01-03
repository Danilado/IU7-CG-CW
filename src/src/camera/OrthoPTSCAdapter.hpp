#ifndef ORTHOGONAL_PTSC_ADAPTER_HPP
#define ORTHOGONAL_PTSC_ADAPTER_HPP

#include "BasePTSCAdapter.hpp"
#include "TransformationMatrix.hpp"

class OrthoPTSCAdapter : public BasePTSCAdapter {
private:
  TransformationMatrix mat;

public:
  std::shared_ptr<Point2D> convert(const Point3D &pt) override;
};

#endif
