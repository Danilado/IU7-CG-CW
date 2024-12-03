#ifndef SHADOWMAP_VISITOR_HPP
#define SHADOWMAP_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "MyPixmap.hpp"
#include "Point3D.hpp"
#include "ShadowMap.hpp"
#include "TransformationMatrix.hpp"
#include <tbb/concurrent_vector.h>
#include <vector>

class ShadowMapVisitor : public BaseVisitor {
private:
  double pitch;
  double yaw;
  std::vector<std::vector<double>> depth;

  TransformationMatrix view;
  tbb::concurrent_vector<MyPixmap> pixmaps;
  double kx, ky;
  double offsetx, offsety;

public:
  explicit ShadowMapVisitor(double pitch, double yaw);
  ~ShadowMapVisitor() = default;

  ShadowMap getSmap() {
    return ShadowMap(std::move(view), {kx, ky}, offsetx, offsety,
                     std::move(depth));
  }

  void visit(WireframeModel &ref) override {};
  void visit(OrthogonalCamera &ref) override {};
  void visit(ProjectionCamera &ref) override {};
  void visit(Scene &ref) override;
  void visit(FaceModel &ref) override;
};

#endif
