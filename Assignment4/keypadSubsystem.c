#include "keypadSubsystem.h"
#include "LCD.h"
#include "print_format.h"
#include "globals.h"
#include <Arduino.h>

void keypadFunction(void* data) {
    keypadData* keyData = (keypadData*) data;
    draw_buttons();

    if (inc_button_pressed()) {
      *(keyData -> solarPanelDriveInc) = TRUE;
    }
    if (dec_button_pressed()) {
      *(keyData -> solarPanelDriveDec) = TRUE;
    }
}
