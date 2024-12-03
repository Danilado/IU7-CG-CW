#include "ShadowMapVisitor.hpp"
#include "Color.hpp"
#include "FaceModel.hpp"
#include "MyMath.hpp"
#include "Scene.hpp"
#include "SingletonTemplate.hpp"
#include <QDebug>
#include <fstream>
#include <limits>
#include <ranges>
#include <tbb/parallel_for_each.h>

#include "BoundingBoxVisitor.hpp"

ShadowMapVisitor::ShadowMapVisitor(double pitch, double yaw) {
  view.reset();
  view.rotate(0., -yaw, 0.);
  view.rotate(pitch, 0., 0.);
}

void ShadowMapVisitor::visit(FaceModel &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  Point3D cam_position = view.apply({0, 0, -1000000});

  auto range =
      ref.getFaces() | // filter visible based on normal vector
      std::views::filter(std::bind(&Face::isVisible, std::placeholders::_1,
                                   cam_position, *transf));

  tbb::parallel_for_each(
      range.begin(), range.end(), [this, &transf](const Face &face) {
        pixmaps.emplace_back(face.getPixmap(
            [transf](const Point3D &pt) { return transf->apply(pt); },
            [this](const Point3D &pt) { return view.apply(pt); },
            [this](const Point3D &pt) {
              return std::make_shared<Point2D>((pt.get_x() - offsetx) * kx,
                                               (pt.get_y() - offsety) * ky);
            },
            depth.front().size(), depth.size(), false));
      });
}

void ShadowMapVisitor::visit(Scene &ref) {
  BoundingBoxVisitor bvis(view);
  bvis.visit(ref);
  auto bbox = bvis.getBounds();

  qDebug() << "boundingBox " << bbox.first.get_x() << "->"
           << bbox.second.get_x() << " " << bbox.first.get_y() << "->"
           << bbox.second.get_y();
  if (abs(bbox.first.get_x() - bbox.second.get_x()) <= MyMath::EPS ||
      abs(bbox.first.get_y() - bbox.second.get_y()) <= MyMath::EPS ||
      std::isinf(bbox.first.get_x()) || std::isinf(bbox.first.get_y()) ||
      std::isinf(bbox.second.get_x()) || std::isinf(bbox.second.get_y())) {
    qDebug() << "BoundingBox is bad";
    return;
  }

  offsetx = bbox.first.get_x();
  offsety = bbox.first.get_y();

  int size_x = bbox.second.get_x() - bbox.first.get_x() + 1;
  int size_y = bbox.second.get_y() - bbox.first.get_y() + 1;

  kx = ky = 1.;
  if (size_x > 1920) {
    kx = 1920. / static_cast<double>(size_x);
    size_x = 1920;
  }
  if (size_y > 1080) {
    ky = 1080. / static_cast<double>(size_y);
    size_y = 1080;
  }

  depth.resize(size_y, std::vector<double>(
                           size_x, std::numeric_limits<double>::infinity()));

  tbb::parallel_for_each(ref.begin(), ref.end(), [this](const auto &newref) {
    newref.second->accept(*this);
  });

  for (const MyPixmap &pmap :
       pixmaps | std::views::filter([](const MyPixmap &pmap) {
         return !pmap.getDepth().empty() && !pmap.getDepth().front().empty();
       })) {
    auto &pdepth = pmap.getDepth();
    auto offset = pmap.getOffset();

    for (int x = 0; x < pdepth.front().size(); ++x)
      for (int y = 0; y < pdepth.size(); ++y) {
        if (std::isinf(pdepth[y][x]))
          continue;
        if (pdepth[y][x] < depth[y + offset.second][x + offset.first]) {
          depth[y + offset.second][x + offset.first] = pdepth[y][x];
        }
      }
  }

  std::ofstream aboba("out.txt");

  for (const auto &row : depth) {
    for (const auto &el : row)
      aboba << el << " ";
    aboba << std::endl;
  }

  qDebug() << "ShadowMap created with res: " << depth.front().size()
           << depth.size();
}
