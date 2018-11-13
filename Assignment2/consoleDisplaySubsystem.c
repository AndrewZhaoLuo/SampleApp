#include "globals.h"
#include "consoleDisplaySubsystem.h"

void consoleDisplayFunction(void* data) {
    // Cast to correct pointer
    consoleDisplayData* displayData = (consoleDisplayData*) data;
    printf("SUBSYSTEM CONSOLE:\n");
}
