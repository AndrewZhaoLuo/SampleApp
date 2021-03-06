#include <string.h>
#include <stdio.h>
#include "globals.h"
#include "consoleDisplaySubsystem.h"
#include "print_format.h"
#include "LCD.h"

void consoleDisplayFunction(void* data) {
    // Cast to correct pointer
    consoleDisplayData* displayData = (consoleDisplayData*) data;

    // for debugging
    print_format("SUBSYSTEM CONSOLE:\n");

    // obtain information to convert to strings
    Bool solarPanelState = *(displayData->solarPanelStatePtr);
    unsigned short batteryLevel = *(displayData->batteryLevelPtr);
    unsigned short fuelLevel = *(displayData->fuelLevelPtr);
    unsigned short powerConsumption = *(displayData->powerConsumptionPtr);

    // Create solar panel state string
    char* state;
    if(solarPanelState){
      state = "TRUE";
    } else {
      state = "FALSE";
    }

    // Create battery level string
    char battery[MAX_VALUE_WIDTH];
    snprintf(battery, MAX_VALUE_WIDTH, "%u", batteryLevel);


    // Create fuel level string
    char fuel[MAX_VALUE_WIDTH];
    snprintf(fuel, MAX_VALUE_WIDTH, "%u", fuelLevel);

    // Create power consumption string
    char power[MAX_VALUE_WIDTH];
    snprintf(power, MAX_VALUE_WIDTH, "%u", powerConsumption);

    // Draw a black rectangle on the top half of the screen to refresh it
    tft_set_color(BLACK);
    tft_fill_rect(TEXT_ALIGN_X, Y_STATE, tft_get_width(), Y_POWER, BLACK);

    tft_set_fontsize(FONTSIZE);
    tft_set_color(GREEN);
    tft_display_top(state, TEXT_ALIGN_X, Y_STATE);
    tft_display_top(battery, TEXT_ALIGN_X, Y_BATTERY);
    tft_display_top(fuel, TEXT_ALIGN_X, Y_FUEL);
    tft_display_top(power, TEXT_ALIGN_X, Y_POWER);
}
