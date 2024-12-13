#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Point3D.hpp"
#include "Scene.hpp"
#include "app.hpp"
#include "sceneDataHelper.hpp"
#include <QErrorMessage>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void setupScene();

private:
  Ui::MainWindow *ui;
  App application;
  std::shared_ptr<SceneDataHelper> sdh;
  std::shared_ptr<QGraphicsScene> scene;

  void showError(const char *str);

  void updateScene();
  void keyPressEvent(QKeyEvent *e) override;
  void handleKey(Qt::Key key);

  void moveCamera(double dx, double dy, double dz);
  void rotateCamera(double horizontal, double vertical);

  // void undo();
  // void redo();

private Q_SLOTS:
  void on_generate_clicked();
  void on_pitch_sliderReleased();
  void on_yaw_sliderReleased();
};
#endif // MAINWINDOW_H
