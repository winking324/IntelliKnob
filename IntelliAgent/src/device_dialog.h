// Copyright (c) winking324
// Bluetooth Connect Dialog
// 1. List connected devices on the top; TODO
// 2. Auto scan new devices on dialog open;
// 3. Double click to connect new device; TODO
// 4. Order devices by rssi; TODO
// 5. Update devices(rssi update, insert or remove); TODO
//

#pragma once

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QDialog>
#include <QHash>
#include <QPointer>
#include <QString>
#include <QTableWidget>

#include "circle_progress_bar.h"

namespace intelli_agent {

class DeviceDialog : public QDialog {
  Q_OBJECT
 public:
  explicit DeviceDialog(QWidget *parent = nullptr);

 public slots:
  void CloseDialog();

  void ScanDevice();

  void ScanError(QBluetoothDeviceDiscoveryAgent::Error error);

  void ScanFinished();

  void AddDevice(const QBluetoothDeviceInfo &info);

  void Connect(bool checked);
  void ConnectToDevice(QTableWidgetItem *item);

  void ShowDeviceMenu(const QPoint &pos);

 private:
  QTableWidget *scanning_widget_;
  CircleProgressBar *progress_bar_;
  QHash<QString, QBluetoothDeviceInfo> devices_;

  QPointer<QBluetoothDeviceDiscoveryAgent> discovery_agent_;
};

}  // namespace intelli_agent
