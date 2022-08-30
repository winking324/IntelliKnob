// Copyright (c) winking324
//

#include "bluetooth_connection.h"

namespace intelli_agent {

BluetoothConnection::BluetoothConnection(QObject *parent) : QObject{parent} {}

void BluetoothConnection::ConnectTo(const QBluetoothDeviceInfo &info) {
  if (connected_info_.deviceUuid() == info.deviceUuid()) {
    return;
  }

  if (!controller_.isNull()) {
    controller_->disconnectFromDevice();
  }

  connected_info_ = info;
  controller_.reset(QLowEnergyController::createCentral(info));

  connect(controller_.get(), &QLowEnergyController::connected, this,
          &BluetoothConnection::Connected);
  connect(controller_.get(), &QLowEnergyController::errorOccurred, this,
          &BluetoothConnection::ErrorReceived);
  connect(controller_.get(), &QLowEnergyController::disconnected, this,
          &BluetoothConnection::Disconnected);
  connect(controller_.get(), &QLowEnergyController::serviceDiscovered, this,
          &BluetoothConnection::AddLowEnergyService);
  connect(controller_.get(), &QLowEnergyController::discoveryFinished, this,
          &BluetoothConnection::ServiceScanDone);

  controller_->connectToDevice();
}

void BluetoothConnection::Connected() {
  qInfo() << "connected to device: " << connected_info_.deviceUuid().toString();
  controller_->discoverServices();
}

void BluetoothConnection::Disconnected() {
  if (controller_->state() != QLowEnergyController::UnconnectedState) {
    controller_->disconnectFromDevice();
  }
}

void BluetoothConnection::ErrorReceived(QLowEnergyController::Error e) {
  qInfo() << "Error[" << e << "]: " << controller_->errorString();
}

void BluetoothConnection::AddLowEnergyService(const QBluetoothUuid &uuid) {
  QLowEnergyService *service = controller_->createServiceObject(uuid);
  if (service == nullptr) {
    qInfo() << "create service from uuid: " << uuid.toString() << ", failed";
    return;
  }
  qInfo() << "service name: " << service->serviceName();

  delete service;
}

void BluetoothConnection::ServiceScanDone() { qInfo() << "service scan done"; }

}  // namespace intelli_agent
