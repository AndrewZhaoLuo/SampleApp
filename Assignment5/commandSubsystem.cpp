// Serial will be used to communicate with the Putty terminal
// Serial1 will be used to communicate with the Arduino UNO

#include <Arduino.h>

// because we will be using in C libraries, use C naming conventions
extern "C" {
  #include "commandSubsystem.h"
}

void commandFunction(void* data) {
  // Cast to correct pointer
 
}
