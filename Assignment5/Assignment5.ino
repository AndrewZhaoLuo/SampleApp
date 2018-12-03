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

  // establish initial display
  //consoleDisplayFunction(&displayData);
  //Serial.println("[DEBUG]: INITIALIZATION FINISHED!");
}

void loop() {
  // put your main code here, to run repeatedly:
  scheduleAndRun(&scheduler, &queue);
  if(startTasks){
    batteryConnectionInterrupt();
    solarPanelConnectionInterrupt();
    solarPanelSafetyInterrupt();
    transportDistFreqInterrupt();
    batteryTempAcknowledged();
  }
}
