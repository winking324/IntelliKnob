// Copyright (c) winking324
//

#pragma once

#include <QDialog>
#include <QTableWidget>

namespace intelli_agent {

class DeviceDialog : public QDialog {
  Q_OBJECT
 public:
  DeviceDialog(QWidget *parent);

 private:
  QTableWidget *devices_widget_;
};

}  // namespace intelli_agent
