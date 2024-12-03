#include "Triangle.hpp"
#include <QDebug>
#include <algorithm>
#include <assert.h>

MyPixmap Triangle::getPixmap(
    std::function<Point3D(const Point3D &)> to_world,
    std::function<Point3D(const Point3D &)> to_camera,
    std::function<std::shared_ptr<Point2D>(const Point3D &)> to_screen,
    size_t screen_width, size_t screen_height, const Color &color,
    bool center_axis, std::shared_ptr<ShadowMap> smap) const {
  assert(screen_width > 0);
  assert(screen_height > 0);

  int centerX = center_axis ? static_cast<int>(screen_width / 2) : 0;
  int centerY = center_axis ? static_cast<int>(screen_height / 2) : 0;

  //   qDebug() << "Center: " << centerX << " " << centerY;
  // p1.debug();
  Point3D t0 = to_world(p1);
  Point3D t1 = to_world(p2);
  Point3D t2 = to_world(p3);
  // t0.debug();
  Point3D v0 = to_camera(t0);
  Point3D v1 = to_camera(t1);
  Point3D v2 = to_camera(t2);
  // v0.debug();

  std::shared_ptr<Point2D> pt1_screen = to_screen(v0);
  std::shared_ptr<Point2D> pt2_screen = to_screen(v1);
  std::shared_ptr<Point2D> pt3_screen = to_screen(v2);

  Point2D p0_2d(pt1_screen->get_x() + centerX, pt1_screen->get_y() + centerY);
  Point2D p1_2d(pt2_screen->get_x() + centerX, pt2_screen->get_y() + centerY);
  Point2D p2_2d(pt3_screen->get_x() + centerX, pt3_screen->get_y() + centerY);

  // Сортировка по Y
  if (p1_2d.get_y() < p0_2d.get_y()) {
    std::swap(p0_2d, p1_2d);
    std::swap(v0, v1);
    std::swap(t0, t1);
  }
  if (p2_2d.get_y() < p1_2d.get_y()) {
    std::swap(p1_2d, p2_2d);
    std::swap(v1, v2);
    std::swap(t1, t2);
  }
  if (p1_2d.get_y() < p0_2d.get_y()) {
    std::swap(p0_2d, p1_2d);
    std::swap(v0, v1);
    std::swap(t0, t1);
  }

  auto interpolate = [](double y1, double x1, double y2, double x2, double y) {
    if (y1 == y2)
      return x1;
    return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
  };

  auto interpolateZ = [](double y1, double z1, double y2, double z2, double y) {
    if (y1 == y2)
      return z1;
    return z1 + (z2 - z1) * (y - y1) / (y2 - y1);
  };

  auto interpolatePart = [](double v1, double v2, int y1, int y2, int y) {
    return v1 + (v2 - v1) * (y - y1) / static_cast<double>(y2 - y1);
  };

  auto interpolatePoint = [&interpolatePart](const Point3D &p1,
                                             const Point3D &p2, int y1, int y2,
                                             int y) {
    return Point3D(interpolatePart(p1.x, p2.x, y1, y2, y),
                   interpolatePart(p1.y, p2.y, y1, y2, y),
                   interpolatePart(p1.z, p2.z, y1, y2, y));
  };

  int minY = std::max(0, static_cast<int>(std::floor(p0_2d.get_y())));
  int minYClamped = std::clamp(minY, 0, static_cast<int>(screen_height));
  int maxY =
      std::min(static_cast<int>(screen_height),
               static_cast<int>(std::ceil(p2_2d.get_y()))) +
      1; // since the coordinates go from 0 to N but indices from 0 to N+1
  int maxYClamped = std::clamp(maxY, 0, static_cast<int>(screen_height));

  int minX = std::min({static_cast<int>(p0_2d.get_x()),
                       static_cast<int>(p1_2d.get_x()),
                       static_cast<int>(p2_2d.get_x())});
  int minXClamped = std::clamp(minX, 0, static_cast<int>(screen_width));
  int maxX =
      std::max({static_cast<int>(p0_2d.get_x()),
                static_cast<int>(p1_2d.get_x()),
                static_cast<int>(p2_2d.get_x())}) +
      1; // since the coordinates go from 0 to N but indices from 0 to N+1
  int maxXClamped = std::clamp(maxX, 0, static_cast<int>(screen_width));

  //   qDebug() << "Allocating " << maxXClamped - minXClamped << " " << maxY -
  //   minY << " " << minX << " " << minY << " " << minXClamped << " "
  //            << maxXClamped;

  if (maxXClamped - minXClamped <= 0 || maxYClamped - minYClamped <= 0)
    return MyPixmap(0, 0);

  MyPixmap res(maxXClamped - minXClamped, maxYClamped - minYClamped,
               minXClamped, minYClamped, bool(smap));

  std::vector<std::vector<double>> &depth = res.getDepthE();
  std::vector<std::vector<double>> &brightness = res.getBrightnessE();
  res.setColor(color);

  for (int y = minYClamped; y < maxYClamped; ++y) {
    double xLeft, xRight, zLeft, zRight;
    Point3D worldLeft, worldRight;

    if (y < p1_2d.get_y()) {
      xLeft = interpolate(p0_2d.get_y(), p0_2d.get_x(), p1_2d.get_y(),
                          p1_2d.get_x(), y);
      xRight = interpolate(p0_2d.get_y(), p0_2d.get_x(), p2_2d.get_y(),
                           p2_2d.get_x(), y);
      zLeft =
          interpolateZ(p0_2d.get_y(), v0.get_z(), p1_2d.get_y(), v1.get_z(), y);
      zRight =
          interpolateZ(p0_2d.get_y(), v0.get_z(), p2_2d.get_y(), v2.get_z(), y);

      worldLeft = interpolatePoint(t0, t1, p0_2d.get_y(), p1_2d.get_y(), y);
      worldRight = interpolatePoint(t0, t2, p0_2d.get_y(), p2_2d.get_y(), y);
    } else {
      xLeft = interpolate(p1_2d.get_y(), p1_2d.get_x(), p2_2d.get_y(),
                          p2_2d.get_x(), y);
      xRight = interpolate(p0_2d.get_y(), p0_2d.get_x(), p2_2d.get_y(),
                           p2_2d.get_x(), y);
      zLeft =
          interpolateZ(p1_2d.get_y(), v1.get_z(), p2_2d.get_y(), v2.get_z(), y);
      zRight =
          interpolateZ(p0_2d.get_y(), v0.get_z(), p2_2d.get_y(), v2.get_z(), y);

      worldLeft = interpolatePoint(t1, t2, p1_2d.get_y(), p2_2d.get_y(), y);
      worldRight = interpolatePoint(t0, t2, p0_2d.get_y(), p2_2d.get_y(), y);
    }

    if (xLeft > xRight) {
      std::swap(xLeft, xRight);
      std::swap(zLeft, zRight);
      std::swap(worldLeft, worldRight);
    }

    int xStart = std::max(minXClamped, static_cast<int>(std::floor(xLeft)));
    int xEnd = std::min(maxXClamped, static_cast<int>(std::ceil(xRight) + 1.));

    if (xEnd - xStart <= 1)
      continue;

    double z = zLeft;
    double dz = (xEnd > xStart) ? (zRight - zLeft) / (xRight - xLeft) : 0;

    Point3D world = worldLeft;
    Point3D d_world = (xEnd > xStart)
                          ? (worldRight - worldLeft) / (xRight - xLeft)
                          : Point3D();

    if (std::ceil(xLeft) < xStart) {
      z += dz * (xStart - xLeft);
      world += d_world * (xStart - xLeft);
    }

    for (int x = xStart; x < xEnd; ++x) {
      depth[y - minYClamped][x - minXClamped] = z;
      if (smap) {
        brightness[y - minYClamped][x - minXClamped] =
            smap->getBrightness(world);
      }
      z += dz;
      world += d_world;
    }
  }

  return res;
}

/*
for (int y = minYClamped; y < maxYClamped; ++y) {
    double xLeft, xRight, zLeft, zRight;

    if (y < p1_2d.get_y()) {
      xLeft = interpolate(p0_2d.get_y(), p0_2d.get_x(), p1_2d.get_y(),
                          p1_2d.get_x(), y);
      xRight = interpolate(p0_2d.get_y(), p0_2d.get_x(), p2_2d.get_y(),
                           p2_2d.get_x(), y);
      zLeft =
          interpolateZ(p0_2d.get_y(), v0.get_z(), p1_2d.get_y(), v1.get_z(), y);
      zRight =
          interpolateZ(p0_2d.get_y(), v0.get_z(), p2_2d.get_y(), v2.get_z(), y);
    } else {
      xLeft = interpolate(p1_2d.get_y(), p1_2d.get_x(), p2_2d.get_y(),
                          p2_2d.get_x(), y);
      xRight = interpolate(p0_2d.get_y(), p0_2d.get_x(), p2_2d.get_y(),
                           p2_2d.get_x(), y);
      zLeft =
          interpolateZ(p1_2d.get_y(), v1.get_z(), p2_2d.get_y(), v2.get_z(), y);
      zRight =
          interpolateZ(p0_2d.get_y(), v0.get_z(), p2_2d.get_y(), v2.get_z(), y);
    }

    if (xLeft > xRight) {
      std::swap(xLeft, xRight);
      std::swap(zLeft, zRight);
    }

    int xStart = std::max(minXClamped, static_cast<int>(std::floor(xLeft)));
    int xEnd = std::min(maxXClamped, static_cast<int>(std::ceil(xRight) + 1.));

    if (xEnd - xStart <= 1)
      continue;

    double z = zLeft;
    double dz = (xEnd > xStart) ? (zRight - zLeft) / (xRight - xLeft) : 0;

    if (std::ceil(xLeft) < xStart)
      z += dz * (xStart - xLeft);

    for (int x = xStart; x < xEnd; ++x) {
      depth[y - minYClamped][x - minXClamped] = z;
      if (smap) {
        brightness[y - minYClamped][x - minXClamped] =
            smap->getBrightness(Point3D::average(t0, t1, t2));
      }
      z += dz;
    }
  }


MyPixmap Triangle::getPixmap(
    std::function<Point3D(const Point3D &)> to_world,
    std::function<Point3D(const Point3D &)> to_camera,
    std::function<std::shared_ptr<Point2D>(const Point3D &)> to_screen,
    size_t screen_width, size_t screen_height, const Color &color,
    bool center_axis, std::shared_ptr<ShadowMap> smap) const {

  int centerX = center_axis ? static_cast<int>(screen_width / 2) : 0;
  int centerY = center_axis ? static_cast<int>(screen_height / 2) : 0;

  Point3D t1 = to_world(p1);
  Point3D t2 = to_world(p2);
  Point3D t3 = to_world(p3);

  Point3D c1 = to_camera(t1);
  Point3D c2 = to_camera(t2);
  Point3D c3 = to_camera(t3);

  auto s1 = to_screen(c1);
  auto s2 = to_screen(c2);
  auto s3 = to_screen(c3);

  Point2D screen1(s1->x + centerX, s1->y + centerY),
      screen2(s2->x + centerX, s2->y + centerY),
      screen3(s3->x + centerX, s3->y + centerY);

  if (screen1.y > screen2.y)
    std::swap(screen1, screen2), std::swap(c1, c2), std::swap(t1, t2);
  if (screen2.y > screen3.y)
    std::swap(screen2, screen3), std::swap(c2, c3), std::swap(t2, t3);
  if (screen1.y > screen2.y)
    std::swap(screen1, screen2), std::swap(c1, c2), std::swap(t1, t2);

  int minY = std::max(0, static_cast<int>(screen1.y - 1));
  int minYClamped = std::clamp(minY, 0, static_cast<int>(screen_height));
  int maxY = std::min(static_cast<int>(screen_height),
                      static_cast<int>(screen3.y + 1));
  int maxYClamped = std::clamp(maxY, 0, static_cast<int>(screen_height));

  int minX = std::min({static_cast<int>(screen1.x), static_cast<int>(screen2.x),
                       static_cast<int>(screen3.x)});
  int minXClamped = std::clamp(minX, 0, static_cast<int>(screen_width));
  int maxX =
      std::max({static_cast<int>(screen1.x), static_cast<int>(screen2.x),
                static_cast<int>(screen3.x)}) +
      1; // since the coordinates go from 0 to N but indices from 0 to N+1
  int maxXClamped = std::clamp(maxX, 0, static_cast<int>(screen_width));

  if (maxXClamped - minXClamped <= 0 || maxYClamped - minYClamped <= 0)
    return MyPixmap(0, 0);

  MyPixmap res(maxXClamped - minXClamped, maxYClamped - minYClamped,
               minXClamped, minYClamped, bool(smap));

  std::vector<std::vector<double>> &depth = res.getDepthE();
  std::vector<std::vector<double>> &brightness = res.getBrightnessE();
  res.setColor(color);

  auto inverseSlope = [](const Point2D &a, const Point2D &b) -> double {
    return (b.x - a.x) / static_cast<double>(b.y - a.y);
  };

  double dx1 = inverseSlope(screen1, screen3);
  double dx2_top = inverseSlope(screen1, screen2);
  double dx2_bottom = inverseSlope(screen2, screen3);

  // custom lerp
  auto interpolate = [](double v1, double v2, int y1, int y2, int y) {
    return v1 + (v2 - v1) * (y - y1) / static_cast<double>(y2 - y1);
  };

  auto interpolatePoint = [&interpolate](const Point3D &p1, const Point3D &p2,
                                         int y1, int y2, int y) {
    return Point3D(interpolate(p1.x, p2.x, y1, y2, y),
                   interpolate(p1.y, p2.y, y1, y2, y),
                   interpolate(p1.z, p2.z, y1, y2, y));
  };

  auto rasterizeSegment = [&](int y_start, int y_end, double x_left,
                              double x_right, double z_left, double z_right,
                              const Point3D &wleft, const Point3D &wright) {
    Point3D world_left = wleft, world_right = wright;

    for (int y = y_start; y <= y_end; ++y) {
      if (y < 0 || y >= static_cast<int>(screen_height))
        continue;

      double z = z_left;
      double dz = (z_right - z_left) / (x_right - x_left);

      Point3D world = world_left;
      Point3D d_world =
          Point3D((world_right.x - world_left.x) / (x_right - x_left),
                  (world_right.y - world_left.y) / (x_right - x_left),
                  (world_right.z - world_left.z) / (x_right - x_left));

      int x_start = static_cast<int>(std::ceil(x_left));
      int x_end = static_cast<int>(std::floor(x_right));
      for (int x = x_start; x <= x_end; ++x) {
        if (x < 0 || x >= static_cast<int>(screen_width))
          continue;

        depth[y - minYClamped][x - minXClamped] = z;
        if (smap)
          brightness[y - minYClamped][x - minXClamped] =
              smap->getBrightness(world);

        z += dz;
        world.x += d_world.x;
        world.y += d_world.y;
        world.z += d_world.z;
      }
      x_left += dx1;
      x_right += (y < screen2.y ? dx2_top : dx2_bottom);
      z_left = interpolate(c1.z, c3.z, screen1.y, screen3.y, y + 1);
      z_right = interpolate(c1.z, (y < screen2.y ? c2.z : c3.z), screen1.y,
                            (y < screen2.y ? screen2.y : screen3.y), y + 1);

      world_left = interpolatePoint(t1, t3, screen1.y, screen3.y, y + 1);
      world_right =
          interpolatePoint(t1, (y < screen2.y ? t2 : t3), screen1.y,
                           (y < screen2.y ? screen2.y : screen3.y), y + 1);
    }
  };

  // top
  rasterizeSegment(screen1.y, screen2.y - 1, screen1.x, screen1.x, c1.z, c1.z,
                   t1, t1);

  // bottom
  rasterizeSegment(screen2.y, screen3.y - 1, screen2.x, screen2.x, c2.z, c2.z,
                   t2, t2);

  return res;
}
*/