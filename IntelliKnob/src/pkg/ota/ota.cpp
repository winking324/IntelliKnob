// Copyright (c) winking324
// OTA Upgrade
//

#include "pkg/ota/ota.h"

namespace intelliknob {
namespace ota {

void Ota::Setup(const String &name) { ota_dfu_ble_.begin(name); }

}  // namespace ota
}  // namespace intelliknob
