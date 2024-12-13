#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  QApplication a(argc, argv);
  MainWindow w;
  // w.show();
  // w.setupScene();
  return a.exec();
}
