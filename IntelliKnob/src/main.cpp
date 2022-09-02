// Copyright (c) winking324
// Main
//

#include <Arduino.h>
#include <SimpleFOC.h>

#include <algorithm>

#include "internal/display_task.h"
#include "internal/interface_task.h"
#include "internal/motor_task.h"
#include "pkg/base/cpp_feature.h"
#include "pkg/ota/ota.h"

#define FORMAT_SPIFFS_IF_FAILED true

static intelli_knob::DisplayTask display_task = intelli_knob::DisplayTask(0);
static intelli_knob::DisplayTask* display_task_p = &display_task;
static intelli_knob::MotorTask motor_task = intelli_knob::MotorTask(1);

intelli_knob::InterfaceTask interface_task =
    intelli_knob::InterfaceTask(0, motor_task, display_task_p);

static QueueHandle_t knob_state_debug_queue;

void setup() {
  Serial.begin(115200);

  motor_task.begin();
  interface_task.begin();

  display_task.begin();

  // Connect display to motor_task's knob state feed
  motor_task.addListener(display_task.getKnobStateQueue());

  // Create a queue and register it with motor_task to print knob state to
  // serial (see loop() below)
  knob_state_debug_queue = xQueueCreate(1, sizeof(intelli_knob::KnobState));
  assert(knob_state_debug_queue != NULL);

  motor_task.addListener(knob_state_debug_queue);

  // Free up the loop task
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
  // delete task to disable loop
  vTaskDelete(NULL);
}
