// Copyright (c) winking324
//

#pragma once

#include <QMainWindow>

#include "preferences_dialog.h"

namespace intelli_agent {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  PreferencesDialog *preferences_dialog_;
};

}  // namespace intelli_agent
