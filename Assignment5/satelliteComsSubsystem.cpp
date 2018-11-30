#include <Arduino.h>

extern "C" {
  //#include "globals.h"
  #include "satelliteComsSubsystem.h"
  #include "rand1.h"
  #include "print_format.h"
}

void satelliteComsFunction(void* data) {
  // Cast to correct pointer
  satelliteComsData* comsData = (satelliteComsData*) data;

  // Get global command
  if(Serial.available() > 0){
    char incomingByte = Serial.read();
    // If command is X, we are switching between satellite and earth terminal
    if (incomingByte == 'x' || incomingByte == 'X') {
      if(*(comsData->isEarthTerminalPtr)){
        *(comsData->isEarthTerminalPtr) = FALSE;
        print_format("Now in Satellite Terminal mode");
      } else{
        *(comsData->isEarthTerminalPtr) = TRUE;
        print_format("Now in Earth Terminal mode");
      }
    }
    // Otherwise, set the global command to the incoming command and schedule appropriate task
    else {
      *(comsData->commandPtr) = toupper(incomingByte);
      if(*(comsData->isEarthTerminalPtr)){
        *(comsData->schedCommandTaskPtr) = TRUE;
        *(comsData->schedVehicleCommsPtr) = FALSE;
      } else {
        *(comsData->schedCommandTaskPtr) = FALSE;
        *(comsData->schedVehicleCommsPtr) = TRUE;
      }
    }
  } 
  // No new command to read, so don't schedule either command or vehicle task
  else {
    *(comsData->schedCommandTaskPtr) = FALSE;
    *(comsData->schedVehicleCommsPtr) = FALSE;
  }

    *(comsData->thrustCommandPtr) = randomInteger(RANDOM_MIN_CMD, RANDOM_MAX_CMD);

    // Set battery low
    if(*(comsData->batteryLevelPtr) <= LOW_LEVEL_BATTERY_WARNING){
        *(comsData->batteryLowPtr) = TRUE;
    } else {
        *(comsData->batteryLowPtr) = FALSE;
    }

    // Set fuel low
    if(*(comsData->fuelLevelPtr) <= LOW_LEVEL_FUEL_WARNING) {
        *(comsData->fuelLowPtr) = TRUE;
    } else {
        *(comsData->fuelLowPtr) = FALSE;
    }

    if (*(comsData -> last_freq) != NO_NEW_FREQUENCY_INFO){
        //print_format("Image frequency: %d", *comsData -> last_freq);
        *(comsData -> last_freq) = NO_NEW_FREQUENCY_INFO;
    }
    // TODO: THE FOLLOWING MUST PRINT AT A FIVE SECOND RATE
    /*
    print_format("\tFuel Low Warning: %d\n\tBattery Low Warning: %d\n", *(comsData->fuelLowPtr), *(comsData->batteryLowPtr));

    print_format("\tSolar Panel State: %d\n\tBattery Level: %d\n\tFuel Level: %d\n\tPower Consumption: %d\n\tPower Generation: %d\n",
                  *(comsData->solarPanelStatePtr), *(comsData->batteryLevelPtr), *(comsData->fuelLevelPtr), *(comsData->powerConsumptionPtr), *(comsData->powerGenerationPtr));
                  */
}
