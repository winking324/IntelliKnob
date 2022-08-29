// Copyright (c) winking324
//

#pragma once

#include <QString>

namespace intelli_agent {

struct Preferences {
  float motor_zero_electric_offset = 2.93;
  uint32_t ble_max_scan_count = 5;
  QString connected_device_uuid;
};

}  // namespace intelli_agent
