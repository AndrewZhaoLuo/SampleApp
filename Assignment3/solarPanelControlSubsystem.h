#ifndef SOLARPANELCONTROLSUBSYSTEM_H_INCLUDED
#define SOLARPANELCONTROLSUBSYSTEM_H_INCLUDED

// the speed of the solar panel
#define SOLAR_PANEL_FULL_ON 100
#define SOLAR_PANEL_FULL_OFF 0

// granularity for modifying the solar panel motor speed
#define SOLAR_PANEL_SPEED_INC 25

// time in ms for WM cycle
#define PWM_CYCLE 500
#define PIN_ON 255
#define PIN_OFF 0

typedef struct solarPanelControlStruct {
    Bool* solarPanelState; // are we generating electricity
    Bool* solarPanelDeploy;
    Bool* solarPanelRetract;
    Bool* solarPanelDriveInc;
    Bool* solarPanelDriveDec;
    int* motorDriveSpeed;
} solarPanelControlData;

void solarPanelControlFunction(void* data);

#endif // SOLARPANELCONTROLSUBSYSTEM_H_INCLUDED
