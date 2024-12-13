#ifndef BASE_CAMERA_HPP
#define BASE_CAMERA_HPP

#include "InvisibleObject.hpp"
#include "MyMath.hpp"

class BaseCamera : public InvisibleObject {
public:
  BaseCamera() { apply(); }

  void move(double forward, double vertical, double horizontal);
  void rotate(double horizontal, double vertical);

  void apply();
  Point3D getPosition() const override { return origin; }

protected:
  Point3D origin = {-200, -200, -200};
  double yaw = MyMath::PI / 4.;
  double pitch = MyMath::PI / 8.;
};

#endif
