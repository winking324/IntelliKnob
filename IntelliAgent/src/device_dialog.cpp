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
#include <QSet>
#include <QTableWidgetItem>
#include <QTimer>
#include <QVBoxLayout>

#include "preferences.h"
#include "singleton.h"

namespace intelli_agent {

DeviceDialog::DeviceDialog(QWidget *parent) : QDialog(parent) {
  scan_count_ = Singleton<Preferences>::Instance()->ble_max_scan_count;

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
  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Cancel, this);
  progress_bar_ = new CircleProgressBar(20, this);
  h_layout->addWidget(progress_bar_);
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
  qInfo() << "BLE discovery error: " << error;
  progress_bar_->hide();
  QMessageBox::warning(this, "IntelliAgent",
                       "Scan Error: " + discovery_agent_->errorString(),
                       QMessageBox::Apply);
}

void DeviceDialog::ScanFinished() {
  qInfo() << "BLE discovery finished";
  progress_bar_->hide();
  if (scan_count_ > 0 && --scan_count_ != 0) {
    QTimer::singleShot(10 * 1000, this, &DeviceDialog::ScanDevice);
  }

  QSet<QString> discoverd_device_uuids;
  auto discoverd_devices = discovery_agent_->discoveredDevices();
  for (auto i = discoverd_devices.begin(); i != discoverd_devices.end(); ++i) {
    discoverd_device_uuids.insert(i->deviceUuid().toString());
  }

  erase_if(devices_, [&](decltype(devices_)::iterator device) {
    if (discoverd_device_uuids.find(device.key()) !=
        discoverd_device_uuids.end()) {
      return false;
    }

    auto items = scanning_widget_->findItems(device.value().name(),
                                             Qt::MatchFlag::MatchExactly);
    for (auto i = items.begin(); i != items.end(); ++i) {
      scanning_widget_->removeRow((*i)->row());
    }
    qInfo() << "BLE remote device: " << device->name() << " " << items.size();
    return true;
  });
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
  name_item->setFlags(name_item->flags() & ~Qt::ItemIsEditable);
  name_item->setToolTip(info.name());
  scanning_widget_->setItem(row, 0, name_item);
  scanning_widget_->verticalHeader()->hide();
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
