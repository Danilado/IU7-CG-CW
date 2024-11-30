#include "RenderVisitor.hpp"
#include "CameraManager.hpp"
#include "Color.hpp"
#include "FaceModel.hpp"
#include "MyMath.hpp"
#include "Scene.hpp"
#include "SingletonTemplate.hpp"
#include "WireframeModel.hpp"
#include <QDebug>
#include <limits>
#include <ranges>
#include <tbb/parallel_for_each.h>

namespace {
void rasterizeTriangle(const std::shared_ptr<Point2D> &p0,
                       const std::shared_ptr<Point2D> &p1,
                       const std::shared_ptr<Point2D> &p2, const Point3D &v0,
                       const Point3D &v1, const Point3D &v2, const Color &color,
                       std::vector<std::vector<Color>> &colors,
                       std::vector<std::vector<double>> &depth,
                       size_t screen_width, size_t screen_height) {

  // Смещение центра координат
  int centerX = static_cast<int>(screen_width / 2);
  int centerY = static_cast<int>(screen_height / 2);

  Point2D p0_2d(p0->get_x() + centerX, p0->get_y() + centerY);
  Point2D p1_2d(p1->get_x() + centerX, p1->get_y() + centerY);
  Point2D p2_2d(p2->get_x() + centerX, p2->get_y() + centerY);

  auto edgeFunction = [](const Point2D &a, const Point2D &b, const Point2D &c) {
    return (c.get_x() - a.get_x()) * (b.get_y() - a.get_y()) -
           (c.get_y() - a.get_y()) * (b.get_x() - a.get_x());
  };

  int minX = std::max(0, static_cast<int>(std::floor(std::min(
                             {p0_2d.get_x(), p1_2d.get_x(), p2_2d.get_x()}))));
  int maxX = std::min(static_cast<int>(screen_width - 1),
                      static_cast<int>(std::ceil(std::max(
                          {p0_2d.get_x(), p1_2d.get_x(), p2_2d.get_x()}))));
  int minY = std::max(0, static_cast<int>(std::floor(std::min(
                             {p0_2d.get_y(), p1_2d.get_y(), p2_2d.get_y()}))));
  int maxY = std::min(static_cast<int>(screen_height - 1),
                      static_cast<int>(std::ceil(std::max(
                          {p0_2d.get_y(), p1_2d.get_y(), p2_2d.get_y()}))));

  double area = edgeFunction(p0_2d, p1_2d, p2_2d);

  for (int y = minY; y <= maxY; ++y) {
    for (int x = minX; x <= maxX; ++x) {
      Point2D p(x + 0.5, y + 0.5);

      double w0 = edgeFunction(p1_2d, p2_2d, p) / area;
      double w1 = edgeFunction(p2_2d, p0_2d, p) / area;
      double w2 = edgeFunction(p0_2d, p1_2d, p) / area;

      if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
        double z = w0 * v0.get_z() + w1 * v1.get_z() + w2 * v2.get_z();

        if (z < depth[y][x]) {
          depth[y][x] = z;
          colors[y][x] = color;
        }
      }
    }
  }
}

} // namespace

void RenderVisitor::visit(WireframeModel &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  BaseModelData &modelData = *ref.data;

  CameraManager &cm = Singleton<CameraManager>::instance();

  std::shared_ptr<TransformationMatrix> camtransf =
      cm.getCamera()->getTransformation();

  PTSCAdapter->setCamera(cm.getCamera());

  std::shared_ptr<std::vector<BaseModelData::Edge>> edges =
      modelData.getEdges();

  for (size_t i = 0; i < edges->size(); ++i) {
    std::shared_ptr<Point2D> pt1 = PTSCAdapter->convert(
        camtransf->apply(transf->apply(*((*edges)[i]->first))));
    std::shared_ptr<Point2D> pt2 = PTSCAdapter->convert(
        camtransf->apply(transf->apply(*((*edges)[i]->second))));

    ctx->drawLine(*pt1, *pt2);
  }
}

void RenderVisitor::visit(FaceModel &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();

  CameraManager &cm = Singleton<CameraManager>::instance();

  std::shared_ptr<BaseCamera> cam =
      std::dynamic_pointer_cast<BaseCamera>(cm.getCamera());
  std::shared_ptr<TransformationMatrix> camtransf = cam->getTransformation();

  PTSCAdapter->setCamera(cm.getCamera());
  Point3D cam_position = cam->getPosition();
  auto resolution = ctx->getResolution();

  auto range =
      ref.getFaces() | // filter visible based on normal vector
      std::views::filter(std::bind(&Face::isVisible, std::placeholders::_1,
                                   cam_position, *transf));

  tbb::parallel_for_each(
      range.begin(), range.end(),
      [this, &camtransf, &transf, &resolution](const Face &face) {
        std::vector<Point3D> pts;
        pts.reserve(face.getPoints().size());

        // transform to camera view
        std::ranges::copy(
            std::views::transform(face.getPoints(),
                                  [&camtransf, &transf](const Point3D &pt) {
                                    return camtransf->apply(transf->apply(pt));
                                  }),
            std::back_inserter(pts));

        // filter behind camera
        if (!std::ranges::any_of(pts, [](const Point3D &pt) {
              return pt.get_z() >= -MyMath::EPS;
            }))
          return;

        std::vector<std::shared_ptr<Point2D>> screenpts;
        screenpts.reserve(pts.size());
        std::ranges::copy(
            std::views::transform(
                pts,
                [this](const Point3D &pt) { return PTSCAdapter->convert(pt); }),
            std::back_inserter(screenpts));

        for (size_t i = 1; i + 1 < screenpts.size(); ++i) {
          rasterizeTriangle(screenpts[0], screenpts[i], screenpts[i + 1],
                            pts[0], pts[i], pts[i + 1], face.getColor(), colors,
                            depth, resolution.first, resolution.second);
        }
      });
}

void RenderVisitor::visit(OrthogonalCamera &ref) {}

void RenderVisitor::visit(ProjectionCamera &ref) {}

void RenderVisitor::visit(Scene &ref) {
  auto resolution = ctx->getResolution();
  colors.clear();
  colors.resize(resolution.second);
  for (auto &el : colors)
    el.resize(resolution.first);
  depth.clear();
  depth.resize(resolution.second);
  for (auto &el : depth)
    el.resize(resolution.first, std::numeric_limits<double>::infinity());
  shade.clear();
  // shade.resize(resolution.second);
  // for (auto &el : shade)
  //   el.resize(resolution.first);

  tbb::parallel_for_each(ref.begin(), ref.end(), [this](const auto &newref) {
    newref.second->accept(*this);
  });

  ctx->setImage(colors, shade);
}
