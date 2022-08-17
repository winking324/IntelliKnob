// Copyright (c) winking324
// Main
//

#include <AceButton.h>
#include <Adafruit_VEML7700.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include <HX711.h>
#include <TFT_eSPI.h>

#include <algorithm>

#include "pkg/base/cpp_feature.h"
#include "pkg/ota/ota.h"

void setup() {
  // put your setup code here, to run once:
  // intelliknob::base::Singleton<intelliknob::ota::Ota>::Instance()->Setup(
  // "IntelliKnob");
}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelete(NULL);

  esp_partition_iterator_t it = esp_partition_find(
      ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, nullptr);

  while (it != NULL) {
    const esp_partition_t *partition = esp_partition_get(it);
    printf(
        "Type: %02x SubType %02x Address 0x%06X Size 0x%06X Encryption %i "
        "Label %s\r\n",
        partition->type, partition->subtype, partition->address,
        partition->size, partition->encrypted, partition->label);
    it = esp_partition_next(it);
  }
  esp_partition_iterator_release(it);
}
