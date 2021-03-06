#include <Arduino.h>

extern "C" {
  //#include "globals.h"
  #include "satelliteComsSubsystem.h"
  #include "rand1.h"
  #include "print_format.h"
  #include "clock.h"
}

void satelliteComsFunction(void* data) {
  // Cast to correct pointer
  static unsigned long long firstRunTime = getTimeMillis();
  satelliteComsData* comsData = (satelliteComsData*) data;

  // Get global command
  if(Serial.available() > 0){
    char incomingByte = Serial.read();
    // If command is X, we are switching between satellite and earth terminal
    if (incomingByte == 'x' || incomingByte == 'X' ){
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

  // PS4 Serial communication
  if(Serial2.available() > 0 ) {
	  char incomingByte = Serial2.read();
	  *(comsData->commandPtr) = toupper(incomingByte);
	  *(comsData->schedCommandTaskPtr) = TRUE;
  }

  // If user at earth terminal provided a thrust command, use that. Otherwise, generate random command
  if(*(comsData->userThrustValuePtr)){
    // The command was already set by the command subsystem, so don't generate a random one
    Serial.print("Thruster value: ");
    Serial.println(*(comsData->thrustCommandPtr));
    *(comsData->userThrustValuePtr) = FALSE;
  } else {
    *(comsData->thrustCommandPtr) = randomInteger(RANDOM_MIN_CMD, RANDOM_MAX_CMD);
  }

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

  // No longer necessary
  /*
  if (*(comsData -> last_freq) != NO_NEW_FREQUENCY_INFO){
      //print_format("Image frequency: %d", *comsData -> last_freq);
      *(comsData -> last_freq) = NO_NEW_FREQUENCY_INFO;
  }*/

  // If there is a response, print it
  if (*(comsData -> isNewResponsePtr)){
    // Check if there was a request for data
    if(*(comsData->responseMessagePtr) == "M: Battery Level = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->batteryLevelPtr));
    }else if(*(comsData->responseMessagePtr) == "M: Fuel Level = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->fuelLevelPtr));
    }else if(*(comsData->responseMessagePtr) == "M: Power Consumption = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->powerConsumptionPtr));
    }else if(*(comsData->responseMessagePtr) == "M: Solar Panel State = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->solarPanelStatePtr));
    }else if(*(comsData->responseMessagePtr) == "M: Image Data = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->last_freq));
    }else if(*(comsData->responseMessagePtr) == "M: Power Generation = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->powerGenerationPtr));
    }else if(*(comsData->responseMessagePtr) == "M: Battery Temperature = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->batteryTempPtr));
    }else if(*(comsData->responseMessagePtr) == "M: Transport Distance = "){
      Serial.print(*(comsData->responseMessagePtr));
      Serial.println(*(comsData->transportDistPtr));
    } else {
      Serial.println(*(comsData->responseMessagePtr));
    }

    *(comsData->isNewResponsePtr) = FALSE;
  }

    // TODO: THE FOLLOWING MUST PRINT AT A FIVE SECOND RATE
    unsigned long long curTime = getTimeMillis();
    unsigned long long timeSinceLastPrint = (curTime - firstRunTime);
	if (timeSinceLastPrint >= FIVE_SECONDS) {
		print_format("---------------------------------------");
    print_format("NAME: TRIPLE A INDUSTRIES");
    print_format("DATE: %s", *(comsData->date));
    print_format("OPERATOR: %s", *(comsData->initials));
		print_format("Fuel Low: %d", *(comsData->fuelLowPtr));
		print_format("Battery Low: %d", *(comsData->batteryLowPtr));
		print_format("Solar Panel State: %d", *(comsData->solarPanelStatePtr));
		print_format("Battery Level: %d", *(comsData->batteryLevelPtr));
		print_format("Fuel Level: %d", *(comsData->fuelLevelPtr));
		print_format("Power Consumption: %d", *(comsData->powerConsumptionPtr));
		print_format("Battery Temperature: %d", *(comsData->batteryTempPtr));
		print_format("Transport Distance: %d", *(comsData->transportDistPtr));
		print_format("Image Data: %d", *(comsData->last_freq));
        print_format("Pirate Distance: %d", *(comsData->pirateDistance));
        print_format("Pirate Detected: %d", *(comsData->pirateDetected));
		print_format("---------------------------------------");
		firstRunTime = curTime;
	}
}
