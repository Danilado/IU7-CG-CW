#pragma once

#include "Color.hpp"
#include "ShadowMap.hpp"
#include "TransformationMatrix.hpp"
#include "Triangle.hpp"
#include <stdexcept>
#include <vector>
class Face {
public:
  Face(const Point3D &p1, const Point3D &p2, const Point3D &p3)
      : tr(p1, p2, p3) {}

  Point3D getNormal() const { return tr.getNormal(); }
  std::vector<Point3D> getPoints() const {
    return {tr.getP1(), tr.getP2(), tr.getP3()};
  }
  bool isVisible(const Point3D &camPosition,
                 const TransformationMatrix &transf) const;

  void setColor(const Color &col) { c = col; };
  const Color &getColor() const { return c; }

  MyPixmap
  getPixmap(std::function<Point3D(const Point3D &)> to_world,
            std::function<Point3D(const Point3D &)> to_camera,
            std::function<std::shared_ptr<Point2D>(const Point3D &)> to_screen,
            size_t screen_width, size_t screen_height, bool center_axis = true,
            std::shared_ptr<ShadowMap> smap = nullptr) const {

    return tr.getPixmap(to_world, to_camera, to_screen, screen_width,
                        screen_height, c, center_axis, smap);
  }

private:
  Triangle tr;
  Color c = {0, 0, 0};
};