#include "pirateManagementSubsystem.h"
#include "print_format.h"

void pirateManagementFunction(void* data) {
    pirateManagementData* managementData = (pirateManagementData*) data;
    int enemyDistance = *(managementData -> pirateDistance);

    if (*(managementData -> firePhasor)) {
        *(managementData -> firePhasor) = FALSE;
        if (enemyDistance < THRESHOLD_PHASORS) {
            print_format("FIRING PHASORS, CLEAR WEAPON BAY\n");
        } else {
            print_format("NOT CLEAR TO FIRE PHASORS OFFICER\n");
        }
    }
    if (*(managementData -> fireTorpedo)) {
        *(managementData -> fireTorpedo) = FALSE;
        if (enemyDistance < THRESHOLD_TORPEDO) {
            print_format("FIRING TORPEDOS, CLEAR WEAPON BAY\n");
        } else {
            print_format("NOT CLEAR TO FIRE TORPEDOS OFFICER\n");
        }
    }
}
