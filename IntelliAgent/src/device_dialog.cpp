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
  scanning_widget_->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::Stretch);
  layout->addWidget(scanning_widget_);

  scan_button_ = new QPushButton("Scan", this);
  QDialogButtonBox *buttons = new QDialogButtonBox(this);
  buttons->addButton(scan_button_, QDialogButtonBox::ActionRole);
  buttons->addButton(QDialogButtonBox::Cancel);
  layout->addWidget(buttons);

  setLayout(layout);

  connect(scanning_widget_, &QTableWidget::itemDoubleClicked, this,
          &DeviceDialog::ConnectToDevice);
  connect(scanning_widget_, &QTableWidget::customContextMenuRequested, this,
          &DeviceDialog::ShowDeviceMenu);

  connect(scan_button_, &QPushButton::released, this,
          &DeviceDialog::ScanDevice);
  connect(buttons, &QDialogButtonBox::rejected, this,
          &DeviceDialog::CloseDialog);

  discovery_agent_ = new QBluetoothDeviceDiscoveryAgent();
  discovery_agent_->setLowEnergyDiscoveryTimeout(25000);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &DeviceDialog::AddDevice);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
          this, &DeviceDialog::ScanError);
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::finished, this,
          &DeviceDialog::ScanFinished);
}

void DeviceDialog::CloseDialog() {
  if (discovery_agent_->isActive()) {
    discovery_agent_->stop();
  }

  reject();
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
  qInfo() << "BLE discovery error[" << error
          << "]: " << discovery_agent_->errorString();
  QMessageBox::warning(this, "IntelliAgent",
                       "Scan Error: " + discovery_agent_->errorString(),
                       QMessageBox::Apply);
  scan_button_->setText("Scan");
}

void DeviceDialog::ScanFinished() {
  qInfo() << "BLE discovery finished";
  scan_button_->setText("Scan");
}

void DeviceDialog::AddDevice(const QBluetoothDeviceInfo &info) {
  if (info.name().isEmpty()) return;
  qInfo() << "BLE discovery scan device: " << info.name();

  scanning_widget_->insertRow(scanning_widget_->rowCount());
  int row = scanning_widget_->rowCount() - 1;

  QTableWidgetItem *name_item = new QTableWidgetItem(info.name());
  //  QTableWidgetItem *uuid_item =
  //      new QTableWidgetItem(info.deviceUuid().toString());

  name_item->setFlags(name_item->flags() & ~Qt::ItemIsEditable);
  //  uuid_item->setFlags(uuid_item->flags() & ~Qt::ItemIsEditable);

  //  uuid_item->setToolTip(info.deviceUuid().toString());

  scanning_widget_->setItem(row, 0, name_item);
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
