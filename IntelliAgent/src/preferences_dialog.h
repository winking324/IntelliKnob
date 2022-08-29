// Copyright (c) winking324
//

#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QTabWidget>

namespace intelli_agent {

class PreferencesDialog : public QDialog {
  Q_OBJECT
 public:
  explicit PreferencesDialog(QWidget *parent = nullptr);

 public slots:
  void OnCalibrateMotor();

 private:
  QWidget *GeneralTab();

  QWidget *BluetoothTab();

  QWidget *AdvancedTab();

 private:
  QTabWidget *tabs_;

  QLineEdit *motor_zero_electric_offset_;
};

}  // namespace intelli_agent
