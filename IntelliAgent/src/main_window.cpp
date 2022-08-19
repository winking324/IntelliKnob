// Copyright (c) winking324
//

#include "main_window.h"

namespace intelli_agent {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QIcon icon(":/icon.png");
  icon.setIsMask(true);

  tray_menu_ = new TrayMenu(this);
  tray_icon_ = new QSystemTrayIcon(icon, this);
  tray_icon_->setContextMenu(tray_menu_);
  tray_icon_->show();

  connect(tray_menu_, &TrayMenu::OnExit, this, &MainWindow::Exit);
}

MainWindow::~MainWindow() {}

void MainWindow::Exit() { this->close(); }

}  // namespace intelli_agent
