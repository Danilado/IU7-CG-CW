#pragma once

#include "MyPixmap.hpp"
#include "Plane.hpp"
#include "ShadowMap.hpp"
#include "TransformationMatrix.hpp"
#include <functional>

class Triangle : public Plane {
public:
  Triangle(const Point3D &point1, const Point3D &point2, const Point3D &point3)
      : Plane(point1, point2, point3) {}

  MyPixmap
  getPixmap(std::function<Point3D(const Point3D &)> to_world,
            std::function<Point3D(const Point3D &)> to_camera,
            std::function<std::shared_ptr<Point2D>(const Point3D &)> to_screen,
            size_t screen_width, size_t screen_height, const Color &color,
            const ShadowMap &smap, bool center_axis = true) const;
};
