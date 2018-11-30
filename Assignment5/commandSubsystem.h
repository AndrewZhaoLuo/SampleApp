#ifndef COMMANDSUBSYSTEM_H
#define COMMANDSUBSYSTEM_H

// for TRUE/FALSE
#include "bool.h"

typedef struct commandDataStruct {
  char* commandPtr;
  char* responsePtr;
} commandManagementData;

/*
See specification/report for full functionality
*/
void commandFunction(void* data);

#endif
