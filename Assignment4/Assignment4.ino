extern "C" {
  #include "TCB.h"
  #include "scheduler.h"
  #include "globals.h"
  #include "clock.h"
  #include "LCD.h"
}

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_FORWARD_PWM_PIN, OUTPUT);

  Serial.begin(BAUD_RATE);
  Serial1.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  init_LCD();
  initialize();

  // force as char* to suppress c++ warnings
  const char* SATELLITE_STATUS = "Satellite Status";
  const char* SOLAR_PANEL_DEPLOYED = "Solar Panel Deployed :";
  const char* BATTERY_LEVEL = "Battery Level        :";
  const char* FUEL_LEVEL = "Fuel Level           :";
  const char* POWER_CONSUMPTION = "Power Consumption    :";
  const char* BATTERY_TEMPERATURE = "Battery Temperature  :";
  const char* TRANSPORT_DISTANCE = "Transport Distance   :";
  const char* ANNUNCIATION = "Annunciation";

  // build the outline for the satellite status screen
  tft_clear_top(BLACK);
  tft_set_color(GREEN);
  tft_set_fontsize(DEFAULT_FONT_SIZE);
  tft_display_top(SATELLITE_STATUS, FIELD_ALIGN_X, HEADER_ALIGN_Y);
  tft_set_fontsize(DEFAULT_FONT_SIZE_SMALL);
  tft_display_top(SOLAR_PANEL_DEPLOYED, FIELD_ALIGN_X, Y_STATE);
  tft_display_top(BATTERY_LEVEL, FIELD_ALIGN_X, Y_BATTERY);
  tft_display_top(FUEL_LEVEL, FIELD_ALIGN_X, Y_FUEL);
  tft_display_top(POWER_CONSUMPTION, FIELD_ALIGN_X, Y_POWER);
  tft_display_top(BATTERY_TEMPERATURE, FIELD_ALIGN_X, Y_TEMP);
  tft_display_top(TRANSPORT_DISTANCE, FIELD_ALIGN_X, Y_DIST);

  // and annunciation
  tft_clear_bottom(WHITE);
  tft_set_color(BLACK);
  tft_set_fontsize(DEFAULT_FONT_SIZE);
  tft_display_bottom(ANNUNCIATION, FIELD_ALIGN_X, HEADER_ALIGN_Y);

  // establish initial display
  consoleDisplayFunction(&displayData);
  Serial.println("[DEBUG]: INITIALIZATION FINISHED!");
}

void loop() {
  // put your main code here, to run repeatedly:
  scheduleAndRun(&scheduler, &queue);
  batteryConnectionInterrupt();
  solarPanelConnectionInterrupt();
  solarPanelSafetyInterrupt();
  transportDistFreqInterrupt();
  batteryTempAcknowledged();
}
