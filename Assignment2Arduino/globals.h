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

#include "bool.h"
#include "thrusterSubsystem.h"
#include "satelliteComsSubsystem.h"
#include "warningAlarmSubsystem.h"
#include "powerSubsystem.h"
#include "consoleDisplaySubsystem.h"

unsigned int thrustCommand;
unsigned short batteryLevel;
unsigned short fuelLevel;
unsigned short powerConsumption;
unsigned short powerGeneration;
Bool solarPanelState;
Bool fuelLow;
Bool batteryLow;

// static allocation for structs to use
powerSubsystemData powerData;
thrusterSubsystemData thrusterData;
satelliteComsData comsData;
consoleDisplayData displayData;
warningAlarmData warningData;

void initialize();
#endif // GLOBALS_H_INCLUDED
