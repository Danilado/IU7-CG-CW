#ifndef RENDER_VISITOR_HPP
#define RENDER_VISITOR_HPP

#include "BaseDrawer.hpp"
#include "BasePTSCAdapter.hpp"
#include "BaseVisitor.hpp"
#include "MyPixmap.hpp"
#include "ShadowMap.hpp"
#include <tbb/concurrent_vector.h>

class RenderVisitor : public BaseVisitor {
private:
  std::shared_ptr<BasePTSCAdapter> PTSCAdapter;
  std::shared_ptr<BaseDrawer> ctx;

  std::vector<std::vector<Color>> colors;
  std::vector<std::vector<double>> depth;
  tbb::concurrent_vector<MyPixmap> pixmaps;

  std::shared_ptr<ShadowMap> smap;

public:
  RenderVisitor() = delete;
  RenderVisitor(std::shared_ptr<BasePTSCAdapter> PTSCAdapter,
                std::shared_ptr<BaseDrawer> ctx)
      : PTSCAdapter(PTSCAdapter), ctx(ctx) {}
  ~RenderVisitor() = default;

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
  void visit(FaceModel &ref) override;
};

#endif
