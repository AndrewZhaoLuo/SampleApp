// this file contains global variables which will be
// initialized in initGlobals.c (if they haven't here)
// see specification/report for details on what each field does

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

// Assign human-readable names to some common 16-bit color values
// From the TFT code included in LCD.ino
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFFA0

#define PANEL_CONNECTION_PIN A11
#define PANEL_INTERRUPT_PIN A12
#define BATTERY_IN_PIN A13
#define MOTOR_BACKWARD_PWM_PIN A14
#define MOTOR_FORWARD_PWM_PIN A15

#define COMS_DATA_TCB 0
#define THRUSTER_DATA_TCB 1
#define POWER_DATA_TCB 2
#define WARNING_DATA_TCB 3
#define DISPLAY_DATA_TCB 4
#define VEHICLE_DATA_TCB 5
#define PANEL_DATA_TCB 6
#define KEYPAD_DATA_TCB 7

#include "bool.h"
#include "thrusterSubsystem.h"
#include "satelliteComsSubsystem.h"
#include "warningAlarmSubsystem.h"
#include "powerSubsystem.h"
#include "consoleDisplaySubsystem.h"
#include "solarPanelControlSubsystem.h"
#include "circularBuffer.h"
#include "vehicleCommsSubsystem.h"
#include "keypadSubsystem.h"
#include "TCB.h"
#include "scheduler.h"

// length of the TCB queue
#define LENGTH 8

// kernels and stuff
TCB tcbs[LENGTH];
Scheduler scheduler;
Taskqueue queue;

// global variables
int motorSpeed;
unsigned int thrustCommand;
unsigned short batteryLevel;
unsigned short fuelLevel;
unsigned short powerConsumption;
unsigned short powerGeneration;
Bool solarPanelState;
Bool solarPanelDeploy;
Bool solarPanelRetract;
Bool solarPanelDriveInc;
Bool solarPanelDriveDec;
Bool fuelLow;
Bool batteryLow;
char vehicleCommand;
char vehicleResponse;
unsigned int* batteryLevelPtr;

// interrupt flags for ISRs
volatile Bool batteryConnectedFlag;
volatile long long batteryConnectionTimestamp;

volatile Bool solarPanelConnectedFlag;
volatile Bool solarPanelMoveFlag;

// static allocation for structs to use
powerSubsystemData powerData;
thrusterSubsystemData thrusterData;
satelliteComsData comsData;
consoleDisplayData displayData;
warningAlarmData warningData;
vehicleCommsData vehicleData;
solarPanelControlData panelData;
circularBuffer circBuf;
keypadData keyData;

void initialize();

// interrupts
void batteryConnectionInterrupt();
void solarPanelConnectionInterrupt();
void solarPanelSafetyInterrupt();
#endif // GLOBALS_H_INCLUDED
