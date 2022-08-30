// Copyright (c) winking324
//

#pragma once

#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QLowEnergyController>
#include <QObject>
#include <QSharedPointer>

namespace intelli_agent {

class BluetoothConnection : public QObject {
  Q_OBJECT
 public:
  explicit BluetoothConnection(QObject *parent = nullptr);

  void ConnectTo(const QBluetoothDeviceInfo &info);

 signals:

 public slots:
  void Connected();
  void Disconnected();
  void ErrorReceived(QLowEnergyController::Error e);

  void AddLowEnergyService(const QBluetoothUuid &uuid);
  void ServiceScanDone();

 private:
  QBluetoothDeviceInfo connected_info_;
  QSharedPointer<QLowEnergyController> controller_;
};

}  // namespace intelli_agent
