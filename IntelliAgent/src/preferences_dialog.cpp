// Copyright (c) winking324
//

#include "preferences_dialog.h"

namespace intelli_agent {

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Preferences");
}

}  // namespace intelli_agent
