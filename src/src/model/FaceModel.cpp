#include "FaceModel.hpp"

void FaceModel::accept(BaseVisitor &vis) { return vis.visit(*this); }

std::unique_ptr<Object> FaceModel::clone() const {
  std::unique_ptr<FaceModel> res = std::make_unique<FaceModel>();
  res->restoreMemento(this->createMemento());
  res->data = std::move(data->clone());
  return std::move(res);
}
