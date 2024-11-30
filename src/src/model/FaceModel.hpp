#pragma once

#include "BaseModel.hpp"
#include "Face.hpp"

class RenderVisitor;
class RotateObjectVisitor;
class ScaleObjectVisitor;
class TransformObjectVisitor;
class TranslateObjectVisitor;
class WireframeModelDirector;

class FaceModel : public BaseModel {
  friend RenderVisitor;
  friend RotateObjectVisitor;
  friend ScaleObjectVisitor;
  friend TransformObjectVisitor;
  friend TranslateObjectVisitor;
  friend WireframeModelDirector;

public:
  void accept(BaseVisitor &vis) override;
  std::unique_ptr<Object> clone() const override;
  const std::vector<Face> &getFaces() const { return faces; }

protected:
  std::vector<Face> faces;
};