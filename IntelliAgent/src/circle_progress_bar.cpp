// Copyright (c) winking324
//

#include "circle_progress_bar.h"

#include <QConicalGradient>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>

namespace intelli_agent {

CircleProgressBar::CircleProgressBar(uint32_t size, QWidget *parent)
    : QWidget(parent) {
  rotation_ = 0;
  setMinimumSize(size, size);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &CircleProgressBar::UpdaterRotation);
  timer->start(3);
}

void CircleProgressBar::UpdaterRotation() {
  ++rotation_;
  if (rotation_ == 360) {
    rotation_ = 0;
  }
  update();
}

void CircleProgressBar::paintEvent(QPaintEvent *event) {
  (void)event;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  QRect rec = rect();

  int min_width = qMin(rec.width(), rec.height()) / 2;
  int thickness = min_width / 6;
  rec.adjust(thickness, thickness, -thickness, -thickness);
  min_width = qMin(rec.width(), rec.height()) / 2;

  QConicalGradient gradient(rec.center(), rotation_);
  gradient.setColorAt(0, Qt::transparent);
  gradient.setColorAt(.5, QColor(25, 180, 255));

  QPainterPath path;
  path.addEllipse(rec.center(), min_width, min_width);
  QPainterPath clip_path;
  clip_path.addEllipse(rec.center(), min_width - thickness,
                       min_width - thickness);
  path = path.subtracted(clip_path);

  int seg_num = 8;  // number of segments
  int radius = min_width + 1;
  int t = thickness / 4;  // inter segment width
  int cx = rec.center().x();
  int cy = rec.center().y();

  for (int i = 0; i < seg_num; i++) {
    // calculate inter segment pos
    float angle = 180.0 / seg_num * i + 90;
    float cos1 = qCos(qDegreesToRadians(angle));
    float sin1 = qSin(qDegreesToRadians(angle));
    float cos2 = qCos(qDegreesToRadians(angle + 180));
    float sin2 = qSin(qDegreesToRadians(angle + 180));
    float x1 = cx + radius * cos1;
    float y1 = cy - radius * sin1;
    float x2 = cx + radius * cos2;
    float y2 = cy - radius * sin2;

    QPainterPath line;
    line.moveTo(x1 - sin1 * t, y1 - cos1 * t);
    line.lineTo(x1 + sin1 * t, y1 + cos1 * t);
    line.lineTo(cx, cy);
    line.lineTo(x2 - sin2 * t, y2 - cos2 * t);
    line.lineTo(x2 + sin2 * t, y2 + cos2 * t);
    path = path.subtracted(line);  // subtract inter segment
  }

  painter.fillPath(path, gradient);
}

}  // namespace intelli_agent
