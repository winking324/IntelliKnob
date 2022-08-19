// Copyright (c) winking324
//

#pragma once

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QDialog>
#include <QPointer>
#include <QPushButton>
#include <QTableWidget>

namespace intelli_agent {

class DeviceDialog : public QDialog {
  Q_OBJECT
 public:
  explicit DeviceDialog(QWidget *parent = nullptr);

 public slots:
  void ScanDevice();

  void ScanError(QBluetoothDeviceDiscoveryAgent::Error error);

  void ScanFinished();

  void AddDevice(const QBluetoothDeviceInfo &info);

 private:
 private:
  QPushButton *scan_button_;
  QTableWidget *devices_widget_;

  QPointer<QBluetoothDeviceDiscoveryAgent> discovery_agent_;
};

}  // namespace intelli_agent
