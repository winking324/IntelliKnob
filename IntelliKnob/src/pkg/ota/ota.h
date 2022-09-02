// Copyright (c) winking324
// OTA Upgrade
//

#pragma once  // NOLINT(build/header_guard)

#include "ble_ota_dfu.hpp"

namespace intelli_knob {
inline namespace pkg {
namespace ota {

class Ota {
 public:
  void Setup(const String &name);

 private:
  BLE_OTA_DFU ota_dfu_ble_;
};

}  // namespace ota
}  // namespace pkg
}  // namespace intelli_knob
