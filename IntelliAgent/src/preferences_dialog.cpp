// Copyright (c) winking324
//

#include "preferences_dialog.h"

#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "preferences.h"
#include "singleton.h"

namespace intelli_agent {

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Preferences");

  auto *layout = new QVBoxLayout();

  tabs_ = new QTabWidget(this);
  tabs_->addTab(GeneralTab(), "通用");
  tabs_->addTab(BluetoothTab(), "蓝牙");
  tabs_->addTab(AdvancedTab(), "高级");
  layout->addWidget(tabs_);

  auto *buttons = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  layout->addWidget(buttons);

  setLayout(layout);

  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void PreferencesDialog::OnCalibrateMotor() {
  qInfo() << "calibrate the motor";
  // TODO
  float zero_electric_offset = 0.0;

  motor_zero_electric_offset_->setText(QString::number(zero_electric_offset));
}

QWidget *PreferencesDialog::GeneralTab() {
  auto tab = new QWidget(this);
  auto *layout = new QVBoxLayout();

  auto *l1 = new QHBoxLayout();
  l1->addWidget(new QLabel("传感器校准", this));
  motor_zero_electric_offset_ = new QLineEdit(this);
  auto *validator = new QDoubleValidator(motor_zero_electric_offset_);
  validator->setDecimals(2);
  motor_zero_electric_offset_->setValidator(validator);
  motor_zero_electric_offset_->setText(QString::number(
      Singleton<Preferences>::Instance()->motor_zero_electric_offset));
  l1->addWidget(motor_zero_electric_offset_);
  auto *button = new QPushButton("校准", this);
  l1->addWidget(button);
  layout->addLayout(l1);

  tab->setLayout(layout);

  connect(button, &QPushButton::released, this,
          &PreferencesDialog::OnCalibrateMotor);
  return tab;
}

QWidget *PreferencesDialog::BluetoothTab() {
  auto tab = new QWidget(this);
  return tab;
}

QWidget *PreferencesDialog::AdvancedTab() {
  auto tab = new QWidget(this);
  return tab;
}

}  // namespace intelli_agent
