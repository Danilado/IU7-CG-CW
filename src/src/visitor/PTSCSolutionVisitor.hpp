#ifndef PTSC_SOLUTION_VISITOR_HPP
#define PTSC_SOLUTION_VISITOR_HPP

#include "BaseDrawer.hpp"
#include "BasePTSCAdapter.hpp"
#include "BaseVisitor.hpp"

class PTSCSolutionVisitor : public BaseVisitor {
private:
  std::shared_ptr<BasePTSCAdapter> &dst;

public:
  PTSCSolutionVisitor(std::shared_ptr<BasePTSCAdapter> &dst) : dst(dst) {}
  ~PTSCSolutionVisitor() = default;

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
  void visit(FaceModel &ref) override {};
};

#endif
