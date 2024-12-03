#include "BoundingBoxVisitor.hpp"
#include "FaceModel.hpp"
#include "Scene.hpp"

void BoundingBoxVisitor::visit(Scene &ref) {
  for (const auto &[_, i] : ref) {
    i->accept(*this);
  }
}

void BoundingBoxVisitor::visit(FaceModel &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();

  for (const auto &face : ref.getFaces())
    for (const auto &point : face.getPoints()) {
      auto pt = tmatrix.apply(transf->apply(point));

      if (pt.get_x() < bounds.first.get_x())
        bounds.first.set_x(pt.get_x());
      else if (pt.get_x() > bounds.second.get_x())
        bounds.second.set_x(pt.get_x());

      if (pt.get_y() < bounds.first.get_y())
        bounds.first.set_y(pt.get_y());
      else if (pt.get_y() > bounds.second.get_y())
        bounds.second.set_y(pt.get_y());

      if (pt.get_z() < bounds.first.get_z())
        bounds.first.set_z(pt.get_z());
      else if (pt.get_z() > bounds.second.get_z())
        bounds.second.set_z(pt.get_z());
    }
}