// Copyright (c) winking324
//

#pragma once

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "tray_menu.h"

namespace intelli_agent {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  QSystemTrayIcon *tray_icon_;
  TrayMenu *tray_menu_;
};

}  // namespace intelli_agent
