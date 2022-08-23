// Copyright (c) winking324
//

#include "device_dialog.h"

#include <QAction>
#include <QBluetoothUuid>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QTimer>
#include <QVBoxLayout>

namespace intelli_agent {

DeviceDialog::DeviceDialog(QWidget *parent) : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Device");

  QVBoxLayout *layout = new QVBoxLayout();

  scanning_widget_ = new QTableWidget(this);
  scanning_widget_->setContextMenuPolicy(
      Qt::ContextMenuPolicy::CustomContextMenu);
  scanning_widget_->setColumnCount(1);
  scanning_widget_->setHorizontalHeaderLabels(QStringList{"Devices"});

  auto *header = scanning_widget_->horizontalHeader();
  header->setSectionResizeMode(0, QHeaderView::Stretch);
  header->setSectionsClickable(false);
  header->setSectionsMovable(false);

  scanning_widget_->setGridStyle(Qt::NoPen);
  layout->addWidget(scanning_widget_);

  QHBoxLayout *h_layout = new QHBoxLayout();
  progress_bar_ = new CircleProgressBar(24, this);
  h_layout->addWidget(progress_bar_);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Cancel, this);
  h_layout->addWidget(buttons);

  layout->addLayout(h_layout);
  setLayout(layout);

  connect(scanning_widget_, &QTableWidget::itemDoubleClicked, this,
          &DeviceDialog::ConnectToDevice);
  connect(scanning_widget_, &QTableWidget::customContextMenuRequested, this,
          &DeviceDialog::ShowDeviceMenu);

  connect(buttons, &QDialogButtonBox::rejected, this,
          &DeviceDialog::CloseDialog);

  discovery_agent_ = new QBluetoothDeviceDiscoveryAgent();
  discovery_agent_->setLowEnergyDiscoveryTimeout(5000);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &DeviceDialog::AddDevice);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
          this, &DeviceDialog::ScanError);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::finished, this,
          &DeviceDialog::ScanFinished);

  discovery_agent_->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void DeviceDialog::CloseDialog() {
  if (discovery_agent_->isActive()) {
    discovery_agent_->stop();
  }

  reject();
}

void DeviceDialog::ScanDevice() {
  progress_bar_->show();
  discovery_agent_->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void DeviceDialog::ScanError(QBluetoothDeviceDiscoveryAgent::Error error) {
  qInfo() << "BLE discovery error[" << error
          << "]: " << discovery_agent_->errorString();
  progress_bar_->hide();
  QMessageBox::warning(this, "IntelliAgent",
                       "Scan Error: " + discovery_agent_->errorString(),
                       QMessageBox::Apply);
}

void DeviceDialog::ScanFinished() {
  qInfo() << "BLE discovery finished";
  progress_bar_->hide();
  QTimer::singleShot(10 * 1000, this, &DeviceDialog::ScanDevice);

  // TODO(winking324): remove devices not in
  // discovery_agent_->discoveredDevices();
}

void DeviceDialog::AddDevice(const QBluetoothDeviceInfo &info) {
  if (info.name().isEmpty()) return;
  auto uuid = info.deviceUuid().toString();
  if (devices_.find(uuid) != devices_.end()) {
    return;
  }
  devices_[uuid] = info;
  qInfo() << "BLE discovery scan device: " << info.name() << ", "
          << info.rssi();

  scanning_widget_->insertRow(scanning_widget_->rowCount());
  int row = scanning_widget_->rowCount() - 1;

  QTableWidgetItem *name_item = new QTableWidgetItem(info.name());
  //  QTableWidgetItem *uuid_item =
  //      new QTableWidgetItem(info.deviceUuid().toString());

  name_item->setFlags(name_item->flags() & ~Qt::ItemIsEditable);
  name_item->setToolTip(info.name());
  //  uuid_item->setFlags(uuid_item->flags() & ~Qt::ItemIsEditable);

  //  uuid_item->setToolTip(info.deviceUuid().toString());

  scanning_widget_->setItem(row, 0, name_item);
  scanning_widget_->verticalHeader()->hide();
  //  devices_widget_->setItem(row, 1, uuid_item);
}

void DeviceDialog::Connect(bool checked) {
  (void)checked;
  int row = scanning_widget_->currentRow();
  QTableWidgetItem *item = scanning_widget_->item(row, 0);
  ConnectToDevice(item);
}

void DeviceDialog::ConnectToDevice(QTableWidgetItem *item) {
  qInfo() << "BLE connect to: " << item->text();
  // TODO(winking324):
}

void DeviceDialog::ShowDeviceMenu(const QPoint &pos) {
  QMenu *menu = new QMenu(this);
  QAction *connect_action = new QAction("Connect", menu);
  connect(connect_action, SIGNAL(triggered(bool)), SLOT(Connect(bool)));
  menu->addAction(connect_action);
  menu->popup(scanning_widget_->viewport()->mapToGlobal(pos));
}

}  // namespace intelli_agent
