// Copyright (c) winking324
//

#pragma once

#include <QAction>
#include <QMap>
#include <QMenu>

namespace intelli_agent {

enum class MenuItem {
  kMenuAbout,
  kMenuPreferences,
  kMenuExit,
};

class TrayMenu : public QMenu {
  Q_OBJECT
 public:
  TrayMenu(QWidget *parent);

 private:
  QMap<MenuItem, QAction *> menus_;
};

}  // namespace intelli_agent
