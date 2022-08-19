// Copyright (c) winking324
//

#include "tray_menu.h"

#include <QPair>
#include <QString>
#include <algorithm>

#include "device_dialog.h"
#include "preferences_dialog.h"

namespace intelli_agent {

using MenuItemInitFunc = void (TrayMenu::*)(QAction *);
using MenuItems = std::map<MenuItem, QPair<QString, MenuItemInitFunc>>;

TrayMenu::TrayMenu(QWidget *parent) : QMenu(parent) {
  static const MenuItems kMenuItems = {
      {MenuItem::kPreferences, {"Preferences", &TrayMenu::InitPreferences}},
      {MenuItem::kDevice, {"Device", &TrayMenu::InitDevice}},
      {MenuItem::kAbout, {"About", &TrayMenu::InitAbout}},
      {MenuItem::kExit, {"Exit", &TrayMenu::InitExit}},

  };

  std::for_each(kMenuItems.begin(), kMenuItems.end(),
                [&](const MenuItems::value_type &i) {
                  auto *new_action = new QAction(i.second.first, this);
                  menus_.insert(std::make_pair(i.first, new_action));
                  (this->*(i.second.second))(new_action);
                  addAction(new_action);
                });
}

void TrayMenu::InitPreferences(QAction *action) {
  connect(action, &QAction::triggered, this, [&]() { OpenPreferences(); });
}

void TrayMenu::InitDevice(QAction *action) {
  connect(action, &QAction::triggered, this, [&]() { OpenDevice(); });
}

void TrayMenu::InitAbout(QAction *action) {
  connect(action, &QAction::triggered, this, [&]() { OpenAbout(); });
}

void TrayMenu::InitExit(QAction *action) {
  connect(action, &QAction::triggered, this, &TrayMenu::OnExit);
}

void TrayMenu::OpenPreferences() {
  auto *dialog = new PreferencesDialog(parentWidget());
  dialog->open();
}

void TrayMenu::OpenDevice() {
  auto *dialog = new DeviceDialog(parentWidget());
  dialog->open();
}

void TrayMenu::OpenAbout() {
  // TODO(winking324): open about dialog
}

}  // namespace intelli_agent
