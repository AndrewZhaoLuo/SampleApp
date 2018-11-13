extern "C" {
  #include "TCB.h"
  #include "scheduler.h"
  #include "globals.h"
  #include "clock.h"
  #include "LCD.h"
}

// length of the TCB queue
#define LENGTH 6

// the time in milliseconds to run the task once, empirically
// found by running task alone 10-100000 times and using
// arduino clock to estimate
#define TASK_TIME_SATELLITE_COMS_FUNCTION 0.126L
#define TASK_TIME_THRUSTER_SUBSYSTEM_FUNCTION 0.121L
#define TASK_TIME_POWER_SUBSYSTEM_FUNCTION 0.08L
#define TASK_TIME_WARNING_ALARM_FUNCTION 44.4L
#define TASK_TIME_CONSOLE_DISPLAY_FUNCTION 61.6L
#define TASK_TIME_DUMMY_FUNCTION 0.07L

TCB tcbs[LENGTH];
Scheduler scheduler;
Taskqueue queue;

// a dummy tasks which does nothing... for now.
// required in spec to have 6 length TCB queue
// so this fills the unused 6th slot
void dummy(void* c);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  init_LCD();
  initScheduler(&scheduler);
  initialize();

  initTCB(&tcbs[0], (void*)&comsData, satelliteComsFunction, PRIORITY_LOW, TASK_TIME_SATELLITE_COMS_FUNCTION);
  initTCB(&tcbs[1], (void*)&thrusterData, thrusterSubsystemFunction, PRIORITY_LOW, TASK_TIME_THRUSTER_SUBSYSTEM_FUNCTION);
  initTCB(&tcbs[2], (void*)&powerData, powerSubsystemFunction, PRIORITY_LOW, TASK_TIME_POWER_SUBSYSTEM_FUNCTION);
  initTCB(&tcbs[3], (void*)&warningData, warningAlarmFunction, PRIORITY_HIGH, TASK_TIME_WARNING_ALARM_FUNCTION);
  initTCB(&tcbs[4], (void*)&displayData, consoleDisplayFunction, PRIORITY_LOW, TASK_TIME_CONSOLE_DISPLAY_FUNCTION);
  initTCB(&tcbs[5], (void*)0, dummy, PRIORITY_LOW, TASK_TIME_DUMMY_FUNCTION);

  initTaskQueue(&queue, tcbs, LENGTH);

  // force as char* to suppress c++ warnings
  const char* SATELLITE_STATUS = "Satellite Status";
  const char* SOLAR_PANEL_DEPLOYED = "Solar Panel Deployed :";
  const char* BATTERY_LEVEL = "Battery Level        :";
  const char* FUEL_LEVEL = "Fuel Level           :";
  const char* POWER_CONSUMPTION = "Power Consumption    :";
  const char* ANNUNCIATION = "Annunciation";

  // build the outline for the satellite status screen
  tft_clear_top(BLACK);
  tft_set_color(GREEN);
  tft_set_fontsize(2);
  tft_display_top(SATELLITE_STATUS, FIELD_ALIGN_X, HEADER_ALIGN_Y);
  tft_set_fontsize(1);
  tft_display_top(SOLAR_PANEL_DEPLOYED, FIELD_ALIGN_X, Y_STATE);
  tft_display_top(BATTERY_LEVEL, FIELD_ALIGN_X, Y_BATTERY);
  tft_display_top(FUEL_LEVEL, FIELD_ALIGN_X, Y_FUEL);
  tft_display_top(POWER_CONSUMPTION, FIELD_ALIGN_X, Y_POWER);

  // and annunciation
  tft_clear_bottom(WHITE);
  tft_set_color(BLACK);
  tft_set_fontsize(2);
  tft_display_bottom(ANNUNCIATION, FIELD_ALIGN_X, HEADER_ALIGN_Y);

  // establish initial display
  consoleDisplayFunction(&displayData);
  Serial.println("[DEBUG]: INITIALIZATION FINISHED!");
}

void loop() {
  // put your main code here, to run repeatedly:
  scheduleAndRun(&scheduler, &queue);
}

void dummy(void* c) {}
