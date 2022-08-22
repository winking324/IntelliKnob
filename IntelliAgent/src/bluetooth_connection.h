// Copyright (c) winking324
//

#pragma once

#include <QObject>

namespace intelli_agent {

class BluetoothConnection : public QObject {
  Q_OBJECT
 public:
  explicit BluetoothConnection(QObject *parent = nullptr);

 signals:
};

}  // namespace intelli_agent
