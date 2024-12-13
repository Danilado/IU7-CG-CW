#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "DrawManager.hpp"
#include "DrawerSolution.hpp"
#include "MyMath.hpp"
#include "Point3D.hpp"
#include "QtDrawerFactory.hpp"
#include "RenderCommand.hpp"
#include "SingletonTemplate.hpp"
#include <QMessageBox>

#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->setFocusPolicy(Qt::StrongFocus);
  ui->setupUi(this);
  this->show();
  setupScene();
  sdh = std::make_shared<SceneDataHelper>(*this);
  sdh->addCamera(1, "Camera 1");
}

MainWindow::~MainWindow() {
  scene.reset();
  delete ui;
}

void MainWindow::setupScene() {
  ui->graphicsView->setFrameShape(QFrame::NoFrame);

  auto v = ui->graphicsView->size();
  int screenWidth = v.width() - 3;
  int screenHeight = v.height() - 5;

  qDebug() << screenWidth << " " << screenHeight;
  scene =
      std::make_shared<QGraphicsScene>(0, 0, screenWidth, screenHeight, this);

  // scene->addRect(scene->sceneRect());

  ui->graphicsView->setScene(scene.get());
  ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

  std::shared_ptr<BaseDrawer> drawer =
      DrawerSolution::create<QtDrawerFactory>(scene);

  DrawManager &drawManager = Singleton<DrawManager>::instance();
  drawManager.setDrawer(drawer);
  drawManager.renderScene(MyMath::rad(ui->yaw->value()),
                          MyMath::rad(ui->pitch->value()));
}

void MainWindow::updateScene() {
  try {
    auto cmd = std::make_shared<RenderCommand>(MyMath::rad(ui->yaw->value()),
                                               MyMath::rad(ui->pitch->value()));
    application.exec(cmd);
  } catch (const std::exception &e) {
    showError(e.what());
  }
}

void MainWindow::showError(const char *str) {
  QMessageBox::critical(nullptr, "Ошибка", QString(str));
}
