#include "bool.h"
#include "clock.h"
#include "solarPanelControlSubsystem.h"
#include "globals.h"
#include "print_format.h"
#include <Arduino.h>

/*
 * dutyCycle is between 0 and 100, and is the motor drive speed
 * curTime is curTime
 * handles driving the pin deterministically
 */
void drivePWM(unsigned int dutyCycle, long long curTime, int pin) {
  static int state = PIN_OFF;
  static long long nextChange = PWM_CYCLE; // when to turn off the pin

  if (dutyCycle == SOLAR_PANEL_FULL_OFF) {
    analogWrite(pin, PIN_OFF);
    state = PIN_OFF;
    nextChange = curTime + PWM_CYCLE;
    return;
  } if (dutyCycle == SOLAR_PANEL_FULL_ON) {
    analogWrite(pin, PIN_ON);
    state = PIN_ON;
    nextChange = curTime + PWM_CYCLE;
    return;
  }

  if (curTime > nextChange) {
    if (state == PIN_OFF) {
      state = PIN_ON;
      nextChange = curTime + PWM_CYCLE / SOLAR_PANEL_FULL_ON * dutyCycle;
    } else {
      state = PIN_OFF;
      nextChange = curTime + PWM_CYCLE / SOLAR_PANEL_FULL_ON * (SOLAR_PANEL_FULL_ON - dutyCycle);
    }
  }
  analogWrite(pin, state);
}

void solarPanelControlFunction(void* data) {
    //print_format("SUBSYSTEM SOLAR PANEL\n");
    solarPanelControlData* panelData = (solarPanelControlData*) data;

    // first make sure panel is connected
    if (!solarPanelConnectedFlag) {
        long long curTime = getTimeMillis();
        drivePWM(0, curTime, MOTOR_FORWARD_PWM_PIN);
        return;
    }

    // first change speeds
    int inc = *(panelData -> solarPanelDriveInc);
    int dec = *(panelData -> solarPanelDriveDec);
    if (inc) {
        * panelData -> motorDriveSpeed += SOLAR_PANEL_SPEED_INC;
        *(panelData -> solarPanelDriveInc) = FALSE;
    }
    if (dec) {
        * panelData -> motorDriveSpeed -= SOLAR_PANEL_SPEED_INC;
        *(panelData -> solarPanelDriveDec) = FALSE;
    }

    // ensure speeds don't go over max
    if (*panelData -> motorDriveSpeed > SOLAR_PANEL_FULL_ON) {
        *panelData -> motorDriveSpeed = SOLAR_PANEL_FULL_ON;
    }
    if (*panelData -> motorDriveSpeed < SOLAR_PANEL_FULL_OFF) {
        *panelData -> motorDriveSpeed = SOLAR_PANEL_FULL_OFF;
    }

    if (!solarPanelMoveFlag && (*panelData -> solarPanelDeploy || *panelData -> solarPanelRetract)) {
        *(panelData -> solarPanelState) = !*(panelData -> solarPanelState);
        *panelData -> motorDriveSpeed = SOLAR_PANEL_FULL_OFF;

        *(panelData -> solarPanelDeploy) = FALSE;
        *(panelData -> solarPanelRetract) = FALSE;
    }

    long long curTime = getTimeMillis();

    // drive PWM, drive forward if your state is retracted
    // and backward if you were fully deployed
    if (*(panelData -> solarPanelState) && solarPanelMoveFlag && *(panelData -> solarPanelRetract)) {
        drivePWM(*panelData -> motorDriveSpeed, curTime, MOTOR_FORWARD_PWM_PIN);
    } else if (solarPanelMoveFlag && *(panelData -> solarPanelDeploy)) {
        drivePWM(*panelData -> motorDriveSpeed, curTime, MOTOR_FORWARD_PWM_PIN);
    } else {
        drivePWM(0, curTime, MOTOR_FORWARD_PWM_PIN);
    }
}
