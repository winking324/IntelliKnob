// Copyright (c) winking324
//

#include "device_dialog.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace intelli_agent {

DeviceDialog::DeviceDialog(QWidget *parent) : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Device");

  QVBoxLayout *layout = new QVBoxLayout();

  devices_widget_ = new QTableWidget(this);
  layout->addWidget(devices_widget_);

  auto *buttons = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  layout->addWidget(buttons);

  setLayout(layout);
}

}  // namespace intelli_agent
