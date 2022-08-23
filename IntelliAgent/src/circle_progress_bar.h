// Copyright (c) winking324
//

#pragma once

#include <QWidget>
#include <cstdint>

namespace intelli_agent {

class CircleProgressBar : public QWidget {
  Q_OBJECT
 public:
  explicit CircleProgressBar(uint32_t size, QWidget *parent = nullptr);

 public slots:
  void UpdaterRotation();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  uint32_t rotation_;
};

}  // namespace intelli_agent
