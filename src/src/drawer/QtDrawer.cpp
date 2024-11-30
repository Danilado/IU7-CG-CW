#include "QtDrawer.hpp"
#include <QBrush>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QPolygonF>
#include <QRectF>
#include <QVector>
#include <stdexcept>

void QtDrawer::drawLine(double x1, double y1, double x2, double y2) {
  scene.lock()->addLine(x1, y1, x2, y2);
}

void QtDrawer::drawLine(Point2D &pt1, Point2D &pt2) {
  drawLine(pt1.get_x(), pt1.get_y(), pt2.get_x(), pt2.get_y());
}

void QtDrawer::drawPolygon(const std::vector<std::shared_ptr<Point2D>> &points,
                           const Color &color) {
  QVector<QPointF> pts;
  pts.reserve(points.size());
  for (const auto &pt : points) {
    pts.push_back(QPointF(pt->get_x(), pt->get_y()));
  }

  QPolygonF poly(pts);
  QBrush brush(QColor(color.r, color.g, color.b));

  scene.lock()->addPolygon(poly, QPen(Qt::NoPen), brush);
}

void QtDrawer::clear() { scene.lock()->clear(); }

std::pair<size_t, size_t> QtDrawer::getResolution() const {
  QRectF sceneRect = scene.lock()->sceneRect();
  int width = static_cast<size_t>(sceneRect.width());
  int height = static_cast<size_t>(sceneRect.height());

  return {width, height};
}

void QtDrawer::setImage(const std::vector<std::vector<Color>> &img,
                        const std::vector<std::vector<double>> &brightness) {
  QImage image(img[0].size(), img.size(), QImage::Format_RGB32);

  for (size_t y = 0; y < img.size(); ++y)
    for (size_t x = 0; x < img[0].size(); ++x)
      image.setPixelColor(x, y, QColor(img[y][x].r, img[y][x].g, img[y][x].b));

  QPixmap pixmap = QPixmap::fromImage(image);

  scene.lock()->addPixmap(pixmap)->setPos(0, 0);
}