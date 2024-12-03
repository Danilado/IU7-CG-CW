#pragma once

#include "BaseVisitor.hpp"
#include "Point2D.hpp"
#include "TransformationMatrix.hpp"
#include <limits>
#include <tuple>

class BoundingBoxVisitor : public BaseVisitor {
private:
  std::pair<Point3D, Point3D> bounds = {
      {std::numeric_limits<double>::infinity(),
       std::numeric_limits<double>::infinity(),
       std::numeric_limits<double>::infinity()},
      {-std::numeric_limits<double>::infinity(),
       -std::numeric_limits<double>::infinity(),
       -std::numeric_limits<double>::infinity()}};
  const TransformationMatrix &tmatrix;

public:
  BoundingBoxVisitor() = delete;
  BoundingBoxVisitor(const TransformationMatrix &tmatrix) : tmatrix(tmatrix) {}
  ~BoundingBoxVisitor() = default;

  const std::pair<Point3D, Point3D> &getBounds() { return bounds; }

  void visit(WireframeModel &ref) override {};
  void visit(OrthogonalCamera &ref) override {};
  void visit(ProjectionCamera &ref) override {};
  void visit(Scene &ref) override;
  void visit(FaceModel &ref) override;
};