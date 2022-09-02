// Copyright (c) winking324
//

#pragma once

#include <AceButton.h>
#include <Arduino.h>

#include "internal/display_task.h"
#include "internal/motor_task.h"
#include "internal/task.h"

namespace intelli_knob {
inline namespace internal {

class InterfaceTask : public Task<InterfaceTask>,
                      public ace_button::IEventHandler {
  friend class Task<InterfaceTask>;  // Allow base Task to invoke protected
                                     // run()

 public:
  InterfaceTask(const uint8_t task_core, MotorTask& motor_task,
                DisplayTask* display_task);
  ~InterfaceTask();

  void handleEvent(ace_button::AceButton* button, uint8_t event_type,
                   uint8_t button_state) override;

 protected:
  void run();

 private:
  MotorTask& motor_task_;
  DisplayTask* display_task_;

  int current_config_ = 0;

  void changeConfig(bool next);
};

}  // namespace internal
}  // namespace intelli_knob
