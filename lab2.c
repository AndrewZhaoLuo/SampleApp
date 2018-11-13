
enum myBool { FALSE = 0, TRUE = 1};
typedef enum myBool Bool;

unsigned int thrustCommand;
unsigned short batteryLevel;
unsigned short fuelLevel;
unsigned short powerConsumption;
unsigned short powerGeneration;
Bool solarPanelState;   `
Bool fuelLow;
Bool batteryLow;

typedef struct powerSubsystemDataStruct {
    Bool* solarPanelStatePtr;
    unsigned short* batteryLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    int callCounter;
    Bool increaseConsumption;
} powerSubsystemData;

typedef struct thrusterSubsystemDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* fuelLevelPtr;
} thrusterSubsystemData;

typedef struct satelliteComsDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    Bool* solarPanelStatePtr;
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
} satelliteComsData;

typedef struct consoleDisplayDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    Bool* solarPanelStatePtr;
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
} consoleDisplayData;

typedef struct warningAlarmDataStruct{
    Bool* fuelLow;
    Bool* batteryLow;
    unsigned short* batteryLevel;
    unsigned short* fuelLevel;
} warningAlarmData;

int main(int argc, char argv[]) {

}

void initialize(){
    // Initialize globals
    thrustCommand = 0;
    batteryLevel = 100;
    fuelLevel = 100;
    powerConsumption = 0;
    powerGeneration = 0;
    solarPanelState = FALSE;
    fuelLow = FALSE;
    batteryLow = FALSE;

    // Initialize data structs
    powerSubsystemData powerData = {.solarPanelStatePtr = &solarPanelState, .batteryLevelPtr = &batteryLevel, .powerConsumptionPtr = &powerConsumption, .powerGenerationPtr = &powerGeneration,
                                    .callCounter = 0, .increaseConsumption = TRUE};
    thrusterSubsystemData thrusterData = {.thrustCommandPtr = &thrustCommand, .fuelLevelPtr = &fuelLevel, .left = 0, .right = 0, .up = 0, .down = 0};
    satelliteComsData comsData = {.thrustCommandPtr = &thrustCommand, .batteryLevelPtr = &batteryLevel, .fuelLevelPtr = &fuelLevel, .powerConsumptionPtr = &powerConsumption, .powerGenerationPtr = &powerGeneration,
                                .solarPanelStatePtr = &solarPanelState, .fuelLowPtr = &fuelLow, .batteryLowPtr = &batteryLow, .motorDrive = 0};
    consoleDisplayData displayData = {.thrustCommandPtr = &thrustCommand, .batteryLevelPtr = &batteryLevel, .fuelLevelPtr = &fuelLevel, .powerConsumptionPtr = &powerConsumption, .powerGenerationPtr = &powerGeneration,
                                .solarPanelStatePtr = &solarPanelState, .fuelLowPtr = &fuelLow, .batteryLowPtr = &batteryLow};
    warningAlarmData warningData = {.fuelLow = &fuelLow, .batteryLow = &batteryLow, .batteryLevel = &batteryLevel, .fuelLevel = &fuelLevel};
}

void powerSubsystemFunction(void* data){
    // Cast to correct pointer
    powerSubsystemData* powerData = (powerSubsystemData*) data;

    powerData->callCounter++;

    // Power Consumption
    if(powerData->increaseConsumption) {
        if (powerData->callCounter % 2 == 0) {
            *(powerData->powerConsumptionPtr) += 2;
        } else {
            *(powerData->powerConsumptionPtr)--;
        }
        if (*(powerData->powerConsumptionPtr) > 10) {
            powerData->increaseConsumption = FALSE;
        }
    } else {
        if (powerData->callCounter % 2 == 0) {
            *(powerData->powerConsumptionPtr) -= 2;
        } else {
            *(powerData->powerConsumptionPtr)++;
        }
        if (*(powerData->powerConsumptionPtr) < 5) {
            powerData->increaseConsumption = TRUE;
        }
    }

    // Power Generation
    if(*(powerData->solarPanelStatePtr)) {  // Solar panel is deployed
        if (*(powerData->batteryLevelPtr) > 95) {
            *(powerData->solarPanelStatePtr) = FALSE;
        } else if (*(powerData->batteryLevelPtr) < 50){
            if (powerData->callCounter % 2 == 0) {
                *(powerData->powerGenerationPtr) += 2;
            } else {
                *(powerData->powerGenerationPtr)++;
            }
        } else if (*(powerData->batteryLevelPtr) <= 95 && *(powerData->batteryLevelPtr) >= 50) {
            if (powerData->callCounter % 2 == 0) {
                *(powerData->powerGenerationPtr) += 2;
            }
        }
    } else {  // Solar panel is not deployed
        if (*(powerData->batteryLevelPtr) <= 10) {
            *(powerData->solarPanelStatePtr) = TRUE;
        }
    }

    // Battery Level
    if(!(*(powerData->solarPanelStatePtr)) {  // Solar panel is not deployed
        *(powerData->batteryLevelPtr) = *(powerData->batterLevelPtr) - (3 * (*(powerData->powerConsumption)));
    } else {  // Solar panel is deployed
        *(powerData->batteryLevelPtr) = *(powerData->batteryLevelPtr) - *(powerData->powerConsumption) + *(powerData->powerGeneration);
    }
}

void thrusterSubsystemFunction((void*) data) {
    // Cast to correct pointer
    thrusterSubsystemData* thrusterData = (thrusterSubsystemData*) data;
    int cmd = *(thrusterData->thrustCommandPtr)

    int left = cmd && 1;
    int right = (cmd>>1) && 1;
    int up = (cmd>>2) && 1;
    int down = (cmd>>3) && 1;

    int magnitude = (cmd>>4) && 0b1111;
    int duration = (cmd>>8) && 0b11111111;
}

void satelliteComsFunction((void*) data) {
    // Cast to correct pointer
    satelliteComsData* comsData = (satelliteComsData*) data;


}

void consoleDisplayFunction((void*) data) {
    // Cast to correct pointer
    consoleDisplayData* displayData = (consoleDisplayData*) data;


}

void warningAlarmFunction((void*) data) {
    // Cast to correct pointer
    warningAlarmData* warningData = (warningAlarmData*) data;


}
