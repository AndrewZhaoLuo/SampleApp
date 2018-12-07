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

#define PIRATE_DETECTION_PIN            A9
#define DISTANCE_TRANSPORT_PIN          A10
#define BATTERY_TEMPERATURE_SENSOR1_PIN A11
#define BATTERY_TEMPERATURE_SENSOR2_PIN A12
#define BATTERY_IN_PIN                  A13
#define IMAGE_READ_PIN                  A14
#define MOTOR_FORWARD_PWM_PIN           A15

#define BATTERY_TEMP_CONNECTION   45
#define TRANSPORT_DIST_CONNECTION 47
#define SOLAR_PANEL_SAFETY        49
#define SOLAR_PANEL_CONNECTION    51
#define BATTERY_CONNECTION        53

#define COMS_DATA_TCB               0
#define THRUSTER_DATA_TCB           1
#define POWER_DATA_TCB              2
#define DISPLAY_DATA_TCB            3
#define WARNING_DATA_TCB            4
#define VEHICLE_DATA_TCB            5
#define PANEL_DATA_TCB              6
#define KEYPAD_DATA_TCB             7
#define DISTANCE_TRANSPORT_DATA_TCB 8
#define IMAGE_CAPTURE_DATA_TCB      9
#define COMMAND_DATA_TCB            10
#define PIRATE_DETECTION_TCB        11

#define BAUD_RATE 9600
#define DEFAULT_FONT_SIZE 2
#define DEFAULT_FONT_SIZE_SMALL 1

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
#include "transportDistanceSubsystem.h"
#include "imageCaptureSubsystem.h"
#include "commandSubsystem.h"
#include "pirateDetectionSubsystem.h"
#include "pirateManagementSubsystem.h"

// length of the TCB queue
#define LENGTH 12

// kernels and stuff
TCB tcbs[LENGTH];
Scheduler scheduler;
Taskqueue queue;

// global variables
  // Temperature Alarm System Globals
int tempAlarmState;
unsigned long long tempAlarmTriggeredTime;

int motorSpeed;
int last_freq;
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
char command;
char response;
unsigned short batteryTemp;
unsigned short transportDist;
Bool isEarthTerminal;
Bool schedCommandTask;
Bool schedVehicleComms;
Bool startTasks;
Bool displayOn;
char* responseMessage;
Bool isNewResponse;
Bool userThrustValue;
Bool pirateDetected;
int pirateDistance;
Bool firePhasor;
Bool fireTorpedo;

// data buffers
unsigned int timeIntervalBuf[16 + BUFFER_METADATA_SIZE];
unsigned int meterDistanceBuf[8 + BUFFER_METADATA_SIZE];
unsigned int batteryBuf[16 + BUFFER_METADATA_SIZE];
int batteryTempBuff[16 + BUFFER_METADATA_SIZE];
unsigned int powerBuf[16 + BUFFER_METADATA_SIZE];
signed int fft_in[FFT_BUFFER_SIZE + BUFFER_METADATA_SIZE];
signed int fft_out[FFT_BUFFER_SIZE + BUFFER_METADATA_SIZE];
int freq_buffer[FREQUENCY_BUFFER + BUFFER_METADATA_SIZE];

// interrupt flags for ISRs
volatile Bool batteryConnectedFlag;
volatile long long batteryConnectionTimestamp;
volatile Bool solarPanelConnectedFlag;
volatile Bool solarPanelMoveFlag;
volatile Bool transportDistanceFreqConnectedFlag;

// static allocation for structs to use
powerSubsystemData powerData;
thrusterSubsystemData thrusterData;
satelliteComsData comsData;
consoleDisplayData displayData;
warningAlarmData warningData;
vehicleCommsData vehicleData;
solarPanelControlData panelData;
keypadData keyData;
transportDistanceData transportData;
imageCaptureData imageData;
commandManagementData commandData;
pirateDetectionData detectionData;
pirateManagementData managementData;

void initialize();

// interrupts
void batteryConnectionInterrupt();
void solarPanelConnectionInterrupt();
void solarPanelSafetyInterrupt();
void transportDistFreqInterrupt();
void batteryTempAcknowledged();
#endif // GLOBALS_H_INCLUDED
