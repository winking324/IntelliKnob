// Copyright (c) winking324
//

#pragma once

#include <QAction>
#include <QMenu>
#include <map>

namespace intelli_agent {

enum class MenuItem {
  kPreferences,
  kDevice,
  kAbout,
  kExit,
};

class TrayMenu : public QMenu {
  Q_OBJECT
 public:
  explicit TrayMenu(QWidget *parent = nullptr);

 signals:
  void OnExit();

 private:
  void InitPreferences(QAction *action);

  void InitDevice(QAction *action);

  void InitAbout(QAction *action);

  void InitExit(QAction *action);

  void OpenPreferences();

  void OpenDevice();

  void OpenAbout();

 private:
  std::map<MenuItem, QAction *> menus_;
};

}  // namespace intelli_agent
