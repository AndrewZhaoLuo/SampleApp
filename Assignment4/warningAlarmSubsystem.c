#include <stdio.h>
#include "clock.h"
#include "globals.h"
#include "warningAlarmSubsystem.h"
#include "satelliteComsSubsystem.h" // for warning levels
#include "print_format.h"
#include "LCD.h"
#include "powerSubsystem.h" // for alarm states

// Handles flashing behavior, determines whether state should be on or off
// based on parity bit given. This parity changes based on a nextParityChange timestamp
// in milliseconds. Upon change the next change will happen period milliseconds away.
// The exception is if the light is green in which case we always display the string.
//
// During the proper parity, prints given string in the given color/fontsize at the given
// coordinates.
void flash_display(char* str, int x, int y, int fontsize, int color, int* parity, unsigned long long* nextParityChange, int period) {
  unsigned long long curTime = getTimeMillis();
  if (curTime >= *nextParityChange) {
      *parity = !(*parity);
      *nextParityChange = curTime + period;
  }
  if (!(*parity) && color != GREEN) {
    color = WHITE;
  }

  tft_set_color(color);
  tft_set_fontsize(fontsize);
  tft_display_bottom(str, x, y);
}

void print_display(char* str, int x, int y, int fontsize, int color) {
  tft_set_color(color);
  tft_set_fontsize(fontsize);
  tft_display_bottom(str, x, y);
}


void warningAlarmFunction(void* data) {
    // variables for managing flashing
    // if 1, print with given color, otherwise print black
    static int parityFuel = 0;
    static int parityBattery = 0;
    static int parityAlarm = 0;

    // when to flip the parity bit based on system clock
    static unsigned long long nextChangeFuel = 0;
    static unsigned long long nextChangeBattery = 0;
    static unsigned long long nextChangeAlarm = 0;

    // Cast to correct pointer
    warningAlarmData* warningData = (warningAlarmData*) data;

    unsigned short fuelLevel = *(warningData->fuelLevelPtr);
    unsigned short batteryLevel = *(warningData->batteryLevelPtr);
    Bool fuelLow = *(warningData->fuelLowPtr);  // Fuel is less than or equal to 10
    Bool batteryLow = *(warningData->batteryLowPtr);  // Battery is less than or equal to 10

    tft_set_fontsize(DEFAULT_FONT_SIZE_SMALL);

    int color_fuel, color_battery;

    // determine correct warning colors for anunciation display
    if (batteryLevel > MEDIUM_LEVEL_BATTERY_WARNING) {
      color_battery = GREEN;
      *(warningData->batteryLowPtr) = FALSE;
    } else if (batteryLevel > LOW_LEVEL_BATTERY_WARNING) {
      color_battery = ORANGE;
      *(warningData->batteryLowPtr) = FALSE;
    } else {
      color_battery = RED;
      *(warningData->batteryLowPtr) = TRUE; // flash 1 second period
    }

    if (fuelLevel > MEDIUM_LEVEL_FUEL_WARNING) {
      color_fuel = GREEN;
      *(warningData->fuelLowPtr) = FALSE;   // solid display
    } else if (fuelLevel > LOW_LEVEL_FUEL_WARNING) {
      color_fuel = ORANGE;
      *(warningData->fuelLowPtr) = FALSE;   // flash 2 second period
    } else {
      color_fuel = RED;
      *(warningData->fuelLowPtr) = TRUE;    // flash 2 second period
    }

    // Flashing Alarm warning
    if (*(warningData->tempAlarmStatePtr) == TEMPERATURE_ALARM_TRIGGERED_UNACKNOWLEDGED){
      unsigned long long timeSinceAlarmTriggered = (getTimeMillis() - *(warningData->tempAlarmTriggeredTimePtr));
        //print_format("timeSinceAlarmTriggered: %d", timeSinceAlarmTriggered);

        if (timeSinceAlarmTriggered >= FIFTEEN_SECONDS && ((timeSinceAlarmTriggered % TEN_SECONDS) >= FIVE_SECONDS)) { // flash for 5 seconds
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, WHITE);
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, RED);
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, WHITE);
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, RED);
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, WHITE);
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, RED);
          parityAlarm = !parityAlarm;
        } else {
          parityAlarm = ALARM_OFF;
          print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, RED);
        }
    } else {
      print_display("TEMPERATURE", FLUSH_X_COORD, FLUSH_Y_TEMP, DEFAULT_FONT_SIZE, WHITE);
    }
    // these control flashing behavior for lights.
    flash_display("BATTERY", FLUSH_X_COORD, FLUSH_Y_BATTERY, DEFAULT_FONT_SIZE, color_battery, &parityBattery, &nextChangeBattery, BATTERY_FLASH_PERIOD);
    flash_display("FUEL", FLUSH_X_COORD, FLUSH_Y_FUEL, DEFAULT_FONT_SIZE, color_fuel, &parityFuel, &nextChangeFuel, FUEL_FLASH_PERIOD);
}
