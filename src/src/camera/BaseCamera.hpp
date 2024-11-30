#ifndef BASE_CAMERA_HPP
#define BASE_CAMERA_HPP

#include "InvisibleObject.hpp"

class BaseCamera : public InvisibleObject {
public:
  void move(double forward, double vertical, double horizontal);
  void rotate(double horizontal, double vertical);

  void apply();
  Point3D getPosition() const override { return origin; }

protected:
  Point3D origin = {0, 0, 0};
  double yaw;
  double pitch;
};

#endif
