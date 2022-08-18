// Copyright (c) winking324
//

#include "main_window.h"

namespace intelli_agent {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  preferences_dialog_ = new PreferencesDialog(this);
}

MainWindow::~MainWindow() {}

}  // namespace intelli_agent
