#ifndef BASE_DRAWER_HPP
#define BASE_DRAWER_HPP

#include "Color.hpp"
#include "Point2D.hpp"
#include <memory>
#include <vector>

class BaseDrawer {
private:
public:
  BaseDrawer() = default;
  virtual ~BaseDrawer() = default;

  virtual void drawLine(Point2D &pt1, Point2D &pt2) = 0;
  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
  virtual void drawPolygon(const std::vector<std::shared_ptr<Point2D>> &points,
                           const Color &color) = 0;
  virtual std::pair<size_t, size_t> getResolution() const = 0;
  virtual void setImage(const std::vector<std::vector<Color>> &img,
                        const std::vector<std::vector<double>> &brightness) = 0;
  virtual void clear() = 0;
};

#endif
