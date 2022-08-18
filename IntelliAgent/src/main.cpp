// Copyright (c) winking324
//

#include <QApplication>

#include "main_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  intelli_agent::MainWindow w;
  w.show();
  return a.exec();
}
