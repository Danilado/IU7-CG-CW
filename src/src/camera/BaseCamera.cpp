#include "BaseCamera.hpp"
#include "MyMath.hpp"
#include <QDebug>
#include <algorithm>

void BaseCamera::move(double forward, double vertical, double horizontal) {
  Point3D fwd(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
  fwd = fwd.normalize();

  Point3D up(0, 1, 0);

  Point3D right = (up % fwd).normalize();

  origin += fwd * forward;
  origin += up * vertical;
  origin += right * horizontal;

  apply();
}

void BaseCamera::rotate(double horizontal, double vertical) {
  yaw += horizontal;

  pitch += vertical;
  pitch = std::clamp(pitch, -MyMath::PI / 2, MyMath::PI / 2);

  apply();
}

void BaseCamera::apply() {
  Point3D fwd(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
  fwd = fwd.normalize();

  Point3D tmpup(0, 1, 0);

  Point3D right = (fwd % tmpup).normalize();

  Point3D up = (fwd % right).normalize();

  TransformationMatrix res;

  res.translate(-origin);
  res.rotate(0., -yaw, 0.);
  res.rotate(pitch, 0., 0.);

  transform->replace(std::move(res));
}