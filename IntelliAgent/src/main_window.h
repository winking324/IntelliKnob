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
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void Exit();

 private:
  QSystemTrayIcon *tray_icon_;
  TrayMenu *tray_menu_;
};

}  // namespace intelli_agent
