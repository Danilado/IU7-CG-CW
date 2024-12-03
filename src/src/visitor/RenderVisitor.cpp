#include "RenderVisitor.hpp"
#include "CameraManager.hpp"
#include "Color.hpp"
#include "FaceModel.hpp"
#include "MyMath.hpp"
#include "Scene.hpp"
#include "ShadowMap.hpp"
#include "ShadowMapVisitor.hpp"
#include "SingletonTemplate.hpp"
#include "WireframeModel.hpp"
#include <QDebug>
#include <limits>
#include <ranges>
#include <tbb/parallel_for_each.h>

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
        pixmaps.emplace_back(face.getPixmap(
            [transf](const Point3D &pt) { return transf->apply(pt); },
            [&camtransf](const Point3D &pt) { return camtransf->apply(pt); },
            [this](const Point3D &pt) { return PTSCAdapter->convert(pt); },
            resolution.first, resolution.second, true, smap));
      });
}

void RenderVisitor::visit(OrthogonalCamera &ref) {}

void RenderVisitor::visit(ProjectionCamera &ref) {}

void RenderVisitor::visit(Scene &ref) {
  ShadowMapVisitor sha(0., 0.);
  sha.visit(ref);

  smap = std::make_shared<ShadowMap>(sha.getSmap());
  if (!smap->isValid()) {
    qDebug() << "Invalid shadowmap";
    smap = nullptr;
  }

  auto resolution = ctx->getResolution();
  colors.resize(resolution.second, std::vector<Color>(resolution.first));
  depth.resize(resolution.second,
               std::vector<double>(resolution.first,
                                   std::numeric_limits<double>::infinity()));
  pixmaps.clear();

  tbb::parallel_for_each(ref.begin(), ref.end(), [this](const auto &newref) {
    newref.second->accept(*this);
  });

  qDebug() << "Pixmaps passed: " << pixmaps.size();

  for (const MyPixmap &pmap :
       pixmaps | std::views::filter([](const MyPixmap &pmap) {
         return !pmap.getDepth().empty() && !pmap.getDepth().front().empty();
       })) {
    auto &pdepth = pmap.getDepth();
    auto offset = pmap.getOffset();
    auto &pcolor = pmap.getColor();
    auto &pbright = pmap.getBrightness();

    for (int x = 0; x < pdepth.front().size(); ++x)
      for (int y = 0; y < pdepth.size(); ++y) {
        if (pdepth[y][x] < depth[y + offset.second][x + offset.first]) {
          depth[y + offset.second][x + offset.first] = pdepth[y][x];
          if (smap)
            colors[y + offset.second][x + offset.first] =
                pcolor * pbright[y][x];
          else
            colors[y + offset.second][x + offset.first] = pcolor;
        }
      }
  }

  ctx->setImage(colors);
}
