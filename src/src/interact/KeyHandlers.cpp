#include "mainwindow.hpp"

#include "CameraManager.hpp"
#include "MyMath.hpp"
#include "RotateObjectCommand.hpp"
#include "ScaleObjectCommand.hpp"
#include "SingletonTemplate.hpp"
#include "TranslateObjectCommand.hpp"
#include <QDebug>
#include <QKeyEvent>

void MainWindow::moveCamera(double dx, double dy, double dz) {
  CameraManager &cm = Singleton<CameraManager>::instance();
  std::shared_ptr<BaseCamera> cam =
      std::dynamic_pointer_cast<BaseCamera>(cm.getCamera());

  cam->move(dx, dy, dz);
  updateScene();
}

void MainWindow::rotateCamera(double horizontal, double vertical) {
  CameraManager &cm = Singleton<CameraManager>::instance();
  std::shared_ptr<BaseCamera> cam =
      std::dynamic_pointer_cast<BaseCamera>(cm.getCamera());

  cam->rotate(horizontal, vertical);
  updateScene();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  Qt::Key key = Qt::Key(e->key());
  handleKey(key);
}

using Qt::Key;

void MainWindow::handleKey(Qt::Key key) {
  switch (key) {
  case (Key::Key_W): {
    qDebug() << "W";
    moveCamera(5, 0, 0);
  } break;
  case (Key::Key_D): {
    qDebug() << "D";
    moveCamera(0, 0, 5);
  } break;
  case (Key::Key_S): {
    qDebug() << "S";
    moveCamera(-5, 0, 0);
  } break;
  case (Key::Key_A): {
    qDebug() << "A";
    moveCamera(0, 0, -5);
  } break;
  case (Key::Key_B): {
    qDebug() << "B";
    moveCamera(0, 5, 0);
  } break;
  case (Key::Key_Space): {
    qDebug() << "Space";
    moveCamera(0, -5, 0);
  } break;
  case (Key::Key_I): {
    qDebug() << "I";
    rotateCamera(0, -MyMath::PI / 180.);
  } break;
  case (Key::Key_L): {
    qDebug() << "L";
    rotateCamera(MyMath::PI / 180., 0.);
  } break;
  case (Key::Key_K): {
    qDebug() << "K";
    rotateCamera(0, MyMath::PI / 180.);
  } break;
  case (Key::Key_J): {
    qDebug() << "J";
    rotateCamera(-MyMath::PI / 180., 0.);
  } break;
  default: {
  } break;
  }
}
