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

#define FORMAT_SPIFFS_IF_FAILED true

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  intelliknob::base::Singleton<intelliknob::ota::Ota>::Instance()->Setup(
      "IntelliKnob");
}

void loop() {
  // put your main code here, to run repeatedly:
  // delete task to disable loop
  vTaskDelete(NULL);
}
