#ifndef KEYPADSUBSYSTEM_H_INCLUDED
#define KEYPADSUBSYSTEM_H_INCLUDED
#include "bool.h"

typedef struct keypadSubsystemStruct {
    Bool* solarPanelDriveInc;
    Bool* solarPanelDriveDec;
} keypadData;

void keypadFunction(void* data);

#endif // KEYPADSUBSYSTEM_H_INCLUDED
