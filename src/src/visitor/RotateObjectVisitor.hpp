#ifndef ROTATE_OBJECT_VISITOR_HPP
#define ROTATE_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"
#include <memory>

class TransformationMatrix;
class Object;

class RotateObjectVisitor : public BaseVisitor {
private:
  Point3D rotation;
  Point3D origin;
  bool deg;

  void rotate_object_around_origin(Object &ref);

public:
  RotateObjectVisitor() = delete;
  RotateObjectVisitor(double ax, double ay, double az, bool deg = false);
  RotateObjectVisitor(double ox, double oy, double oz, double ax, double ay,
                      double az, bool deg = false);
  RotateObjectVisitor(const Point3D &angles, bool deg = false);
  RotateObjectVisitor(const Point3D &origin, const Point3D &angles,
                      bool deg = false);

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
  void visit(FaceModel &ref) override;
};

#endif
