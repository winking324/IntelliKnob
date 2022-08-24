// Copyright (c) winking324
//

#pragma once

#include <QString>

namespace intelli_agent {

struct Preferences {
  uint32_t ble_max_scan_count = 5;
  QString connected_device_uuid;
};

}  // namespace intelli_agent
