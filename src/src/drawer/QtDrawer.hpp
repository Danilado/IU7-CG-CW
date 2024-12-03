#ifndef QT_DRAWER_HPP
#define QT_DRAWER_HPP

#include "BaseDrawer.hpp"
#include <QGraphicsScene>
#include <memory>

#include <QImage>

class QtDrawer : public BaseDrawer {
private:
  std::weak_ptr<QGraphicsScene> scene{};

public:
  QtDrawer() = delete;
  explicit QtDrawer(std::weak_ptr<QGraphicsScene> &scene) : scene(scene) {}
  ~QtDrawer() override = default;

  void drawLine(Point2D &pt1, Point2D &pt2) override;
  void drawLine(double x1, double y1, double x2, double y2) override;
  void drawPolygon(const std::vector<std::shared_ptr<Point2D>> &points,
                   const Color &color) override;
  void clear() override;

  std::pair<size_t, size_t> getResolution() const override;
  void setImage(const std::vector<std::vector<Color>> &img) override;
};

#endif
