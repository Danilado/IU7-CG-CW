#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "Color.hpp"
#include "Cube.hpp"
#include "House.hpp"
#include "Roads.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "ShadowMap.hpp"
#include "ShadowMapVisitor.hpp"
#include "SingletonTemplate.hpp"
#include "Square.hpp"
#include "Tree.hpp"

#include "QWFC.hpp"
#include "QWFCHelper.hpp"
#include <QDebug>

namespace {
constexpr double side = 50;
}

void MainWindow::on_generate_clicked() {
  try {
    SceneManager &sm = Singleton<SceneManager>::instance();
    sm.resetScene();

    qDebug() << "Generating...";
    size_t sz_x = ui->xlimits->value();
    size_t sz_y = ui->ylimits->value();
    qDebug() << "Size:" << sz_x << sz_y;
    double coeff_roads = ui->roadprob->value();
    double coeff_houses = ui->houseprob->value();
    double coeff_trees = ui->treeprob->value();
    double coeff_empty = ui->emptyprob->value();

    auto cells = QWFCHelper::GetCells(coeff_roads, coeff_houses, coeff_trees,
                                      coeff_empty);

    QWFC qwf(sz_x, sz_y, cells);
    qwf.run();

    qDebug() << "Generated 2d scene";

    std::vector<Color> gridColors = {Color(0, 255, 0), Color(128, 255, 0)};

    std::map<int, Color> colorful = {
        {0, Color(255, 0, 0)},  {1, Color(255, 0, 0)}, {2, Color(255, 0, 0)},
        {3, Color(255, 0, 0)},  {4, Color(255, 0, 0)}, {5, Color(255, 0, 0)},
        {6, Color(255, 0, 0)},  {7, Color(0, 255, 0)}, {8, Color(88, 57, 39)},
        {9, Color(128, 255, 0)}};

    auto res = qwf.getResult();
    for (size_t y = 0; y < res.size(); ++y)
      for (size_t x = 0; x < res.front().size(); ++x) {
        ObjectPtr obj = std::make_shared<Square>(side, gridColors[(x + y) % 2]);
        obj->move(-side / 2, 50.005, 0);
        obj->move(side * x, 0, side * y);
        sm.addObject(obj);

        ObjectPtr model;
        switch (res[y][x].getId()) {
        case 0:
          model = std::make_shared<CrossRoad>(side, Color(211, 211, 211));
          break;
        case 1:
          model = std::make_shared<HorizontalRoad>(side, Color(211, 211, 211));
          break;
        case 2:
          model = std::make_shared<VerticalRoad>(side, Color(211, 211, 211));
          break;
        case 3:
          model = std::make_shared<BRRoad>(side, Color(211, 211, 211));
          break;
        case 4:
          model = std::make_shared<TRRoad>(side, Color(211, 211, 211));
          break;
        case 5:
          model = std::make_shared<LBRoad>(side, Color(211, 211, 211));
          break;
        case 6:
          model = std::make_shared<TLRoad>(side, Color(211, 211, 211));
          break;
        case 8:
          model = std::make_shared<House>(side * 0.5);
          model->move(side * 0.5 / 2, .5, side * 0.5 / 2);
          break;
        case 9:
          model = std::make_shared<Tree>(side * 0.3);
          model->move(side * 0.5 / 2, .5, side * 0.5 / 2);
        default:
          break;
        }
        if (!model)
          continue;
        model->move(-side / 2, 50, 0);
        model->move(side * x, 0, side * y);
        sm.addObject(model);
      }

    ShadowMap &smap = Singleton<ShadowMap>::instance();
    ShadowMapVisitor vis(MyMath::rad(ui->pitch->value()),
                         MyMath::rad(ui->yaw->value()));

    vis.visit(*sm.getScene());

    smap = std::move(vis.getSmap());

    updateScene();
  } catch (const std::exception &e) {
    showError(e.what());
  }
}

void MainWindow::on_pitch_sliderReleased() {
  try {
    SceneManager &sm = Singleton<SceneManager>::instance();

    ShadowMap &smap = Singleton<ShadowMap>::instance();
    ShadowMapVisitor vis(MyMath::rad(ui->pitch->value()),
                         MyMath::rad(ui->yaw->value()));

    vis.visit(*sm.getScene());

    smap = std::move(vis.getSmap());
    updateScene();
  } catch (const std::exception &e) {
    showError(e.what());
  }
}

void MainWindow::on_yaw_sliderReleased() {
  try {

    SceneManager &sm = Singleton<SceneManager>::instance();

    ShadowMap &smap = Singleton<ShadowMap>::instance();
    ShadowMapVisitor vis(MyMath::rad(ui->pitch->value()),
                         MyMath::rad(ui->yaw->value()));

    vis.visit(*sm.getScene());

    smap = std::move(vis.getSmap());
    updateScene();
  } catch (const std::exception &e) {
    showError(e.what());
  }
}
