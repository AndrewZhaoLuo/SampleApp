// this file contains global variables which will be
// initialized in main.c (if they haven't here)

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

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
