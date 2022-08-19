// Copyright (c) winking324
//

#include "device_dialog.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

namespace intelli_agent {

DeviceDialog::DeviceDialog(QWidget *parent) : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Device");

  QVBoxLayout *layout = new QVBoxLayout();

  devices_widget_ = new QTableWidget(this);
  layout->addWidget(devices_widget_);

  scan_button_ = new QPushButton("Scan", this);
  layout->addWidget(scan_button_);

  setLayout(layout);

  connect(scan_button_, &QPushButton::released, this,
          &DeviceDialog::ScanDevice);

  discovery_agent_ = new QBluetoothDeviceDiscoveryAgent();
  discovery_agent_->setLowEnergyDiscoveryTimeout(25000);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &DeviceDialog::AddDevice);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
          this, &DeviceDialog::ScanError);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::finished, this,
          &DeviceDialog::ScanFinished);
}

void DeviceDialog::ScanDevice() {
  if (scan_button_->text() == "Scan") {
    discovery_agent_->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    scan_button_->setText("Stop");
  } else {
    qInfo() << "BLE discovery stopped";
    discovery_agent_->stop();
    scan_button_->setText("Scan");
  }
}

void DeviceDialog::ScanError(QBluetoothDeviceDiscoveryAgent::Error error) {
  qInfo() << "BLE discovery error: " << error;
  scan_button_->setText("Scan");
}

void DeviceDialog::ScanFinished() {
  qInfo() << "BLE discovery finished";
  scan_button_->setText("Scan");
}

void DeviceDialog::AddDevice(const QBluetoothDeviceInfo &info) {
  (void)info;
  qInfo() << "BLE discovery scan device: " << info.name();
  // TODO(winking324):
}

}  // namespace intelli_agent
